#pragma once

#include <atomic>
#include <cinttypes>
#include <vector>

#include "memory.h"
#include "meta.h"
#include "print.h"
#include "types.h"

namespace task_scheduler
{

    template < class TMemInterface > class base_task_graph;
    template < class TMemInterface > class base_thread_pool;
    template < class TMemInterface > struct base_thread;
    template < class task_type, class TMemInterface > struct base_sub_graph;

    template < class TMemInterface > class base_task : public TMemInterface
    {
      public:
        typedef base_task< TMemInterface > task_type;
        typedef base_thread< TMemInterface > thread_type;
        typedef base_task_graph< TMemInterface > task_graph_type;
        typedef base_sub_graph< task_type, TMemInterface > sub_graph_type;
        typedef std::basic_string< char, std::char_traits< char >, stl_allocator< char, TMemInterface > > string_type;
        typedef std::vector< string_type, stl_allocator< string_type, TMemInterface > > string_vector;
        typedef std::vector< task_type *, stl_allocator< task_type *, TMemInterface > > task_vector;
        typedef base_thread_pool< TMemInterface > thread_pool;
        typedef std::function< void() > function_type;
        typedef int64_t rank_type;
        typedef std::vector< function_type > task_work_vector;
        typedef thread_index_t< TMemInterface > thread_index_type;

        typedef lock_free_node_dispenser< function_type *, TMemInterface > work_memory_allocator_type;
        typedef lock_free_queue<
            multi_producer_multi_consumer< function_type *, TMemInterface, work_memory_allocator_type >,
            function_type *, TMemInterface, work_memory_allocator_type * >
            work_queue_type;

        enum priority_selector
        {
            realtime,
            high,
            normal,
            low,
            num_priority
        };

        struct debug_container
        {
            const char *priority_to_string(priority_selector _priority) const;

            string_type task_name;
            string_vector dependent_task_names;
        };

        struct transient_container
        {
            transient_container();
            ~transient_container();

            std::atomic_int64_t start_gate;
            work_queue_type *work_queue;
            work_memory_allocator_type work_allocator;
            std::atomic_int64_t num_working;
        };

        struct persistent_container
        {
            persistent_container();
            ~persistent_container();

            priority_selector task_priority;
            task_vector parent_tasks;
            task_vector dependent_tasks;
            task_vector kick_tasks;
            sub_graph_type *sub_graph;
            rank_type rank;
            int64_t thread_affinity;
            task_work_vector task_work;
        };

        void set_thread_affinity(thread_mask_int_t _mask);
        void set_thread_exclusion(thread_mask_int_t _mask);
        void set_num_workers(thread_num_t _num_workers);
        void set_num_workers(percentage_t _percentage_workers);
        base_task(task_graph_type &_task_graph);
        ~base_task();
        void finalize();
        void kick_dependent_tasks();
        bool add_task_parallel_work(function_type _work_function);
        bool operator()();
        bool link_task(task_type *_next_task);

        debug_container debug;
        transient_container transient;
        persistent_container persistent;
        task_graph_type &task_graph;

        thread_unsafe_access_storage add_task_parallel_work_detector;
    };

    template < class TMemInterface >
    const char *base_task< TMemInterface >::debug_container::priority_to_string(priority_selector priority) const
    {
        static const char *priority_to_string[] = {"REALTIME", "HIGH", "NORMAL", "LOW"};

        return priority_to_string[uint32_t(priority)];
    }

    template < class TMemInterface >
    base_task< TMemInterface >::persistent_container::persistent_container()
        : task_priority(normal)
        , sub_graph(nullptr)
        , rank(0)
        , thread_affinity(0)
    {
    }

    template < class TMemInterface > base_task< TMemInterface >::persistent_container::~persistent_container() {}

    template < class TMemInterface >
    base_task< TMemInterface >::transient_container::transient_container()
        : work_queue(nullptr)
        , num_working(0)
    {
        work_queue = new work_queue_type(&work_allocator);
    }

    template < class TMemInterface > base_task< TMemInterface >::transient_container::~transient_container()
    {
        assert(work_queue);
        delete work_queue;
        work_queue = nullptr;
    }

    template < class TMemInterface > bool base_task< TMemInterface >::operator()()
    {
        function_type *work_function = nullptr;
        if (transient.work_queue->pop_front(work_function))
        {
            (*work_function)();
            return true;
        }
        return false;
    }

    template < class TMemInterface > void base_task< TMemInterface >::set_thread_affinity(thread_mask_int_t _mask)
    {
        task_graph.set_task_thread_affinity(this, _mask);
    }

    template < class TMemInterface > void base_task< TMemInterface >::set_thread_exclusion(thread_mask_int_t _mask)
    {
        task_graph.set_task_thread_exclusion(this, _mask);
    }

    template < class TMemInterface > void base_task< TMemInterface >::set_num_workers(thread_num_t _num_workers)
    {
        task_graph.set_num_workers(this, _num_workers);
    }

    template < class TMemInterface > void base_task< TMemInterface >::set_num_workers(percentage_t _percentage_workers)
    {
        task_graph.set_percentage_of_workers(this, _percentage_workers);
    }

    template < class TMemInterface >
    base_task< TMemInterface >::base_task(task_graph_type &_task_graph)
        : task_graph(_task_graph)
    {
    }

    template < class TMemInterface > base_task< TMemInterface >::~base_task() { persistent.task_work.clear(); }

    template < class TMemInterface > void base_task< TMemInterface >::finalize()
    {
        for (auto &work : persistent.task_work)
        {
            transient.work_queue->push_back(&work);
        }
    }

    template < class TMemInterface > void base_task< TMemInterface >::kick_dependent_tasks()
    {
        // Reduce queue rank of queue that the current task is running on
        task_graph.pool.queue_rank[persistent.task_priority][task_graph.pool.get_current_thread()->thread_index]
            .fetch_sub(persistent.rank);

        // Queue dependent tasks only when their start gates are 0
        // i.e. all parent tasks have been executed

        // If we are scheduling many tasks at once search for the next best ranked queue, starting from just after the
        // queue that was just scheduled
        reduce_starvation(new_search_index) thread_index_type best_search_index =
            task_graph.pool.get_current_thread()->thread_index;

        for (auto dependent_task : persistent.dependent_tasks)
        {
            if (--dependent_task->transient.start_gate == 0)
            {
                // Find lowest ranking queue, aka best queue and increment its rank with dependent task rank
                thread_type *best_thread = nullptr;
                rank_type best_rank = std::numeric_limits< rank_type >::max();
                do
                {
                    best_thread = nullptr;
                    best_rank = std::numeric_limits< rank_type >::max();
                    thread_index_type current_thread_index = best_search_index;
                    for (thread_num_t iterations = 0; iterations < task_graph.pool.num_threads;
                         ++current_thread_index, ++iterations)
                    {
                        if (!current_thread_index.is_set(dependent_task->persistent.thread_affinity))
                            continue; // Skip threads the task should not run on

                        int64_t current_thread_rank =
                            task_graph.pool.queue_rank[dependent_task->persistent.task_priority][current_thread_index]
                                .load();
                        if (current_thread_rank < best_rank)
                        {
                            best_rank = current_thread_rank;
                            best_thread = task_graph.pool.threads[current_thread_index];
                        }
                    }
                } while (
                    !task_graph.pool.queue_rank[dependent_task->persistent.task_priority][best_thread->thread_index]
                         .compare_exchange_weak(best_rank, best_rank + dependent_task->persistent.rank));

                // Push task into the best queue
                uint32_t dependent_task_priority = dependent_task->persistent.task_priority;
                do
                {
                } while (!best_thread->task_queue[dependent_task_priority]->push_back(dependent_task) &&
                         ++dependent_task_priority < task_type::num_priority);
                assert(dependent_task_priority < task_type::num_priority);

                ts_print("schedule " << dependent_task->debug.task_name << " -> "
                                     << uint32_t(best_thread->thread_index));
                // Wake up thread if its sleeping
                best_thread->wake_up();

                reduce_starvation(new_search_index) best_search_index = best_thread->thread_index;
            }
        }

        // Stop kicking tasks when a request to pause has been received
        // If all tail kickers have paused, then request the threads to stop
        if (persistent.kick_tasks.size() && task_graph.pool.setup.request_exit == thread_pool::request_pause)
        {
            --task_graph.pool.setup.thread_sync;
            if (!task_graph.pool.setup.thread_sync)
            {
                task_graph.pool.setup.request_exit.store(thread_pool::request_stop);
                task_graph.pool.wake_up();
            }
            return;
        }

        // Only Tail task_type Nodes should have kick tasks
        // kick tasks are Head Tasks for the next frame
        bool initializedSubGraph = false;
        for (auto kick_task : persistent.kick_tasks)
        {
            if (!initializedSubGraph)
            {
                task_graph.setup(kick_task->persistent.sub_graph);
                initializedSubGraph = true;
            }
            uint64_t start_gate = kick_task->transient.start_gate.load();
            assert(start_gate == 0);
            (void)start_gate;
            task_graph.queue_task(kick_task);
        }
    }

    template < class TMemInterface > bool base_task< TMemInterface >::link_task(task_type *_next_task)
    {
        return task_graph.link_task(this, _next_task);
    }

    template < class TMemInterface >
    bool base_task< TMemInterface >::add_task_parallel_work(function_type _work_function)
    {
        thread_unsafe_access_guard guard(add_task_parallel_work_detector);
        assert(transient.num_working == 0);
        persistent.task_work.push_back(_work_function);
        transient.work_queue->push_back(&persistent.task_work.back());
        return true;
    }
};