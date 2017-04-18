// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="task.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>
#include <cinttypes>
#include <vector>

#include "memory.h"
#include "meta.h"
#include "print.h"
#include "types.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    template < class TMemInterface > class base_task_graph;
    template < class TMemInterface > class base_thread_pool;
    template < class TMemInterface > struct base_thread;
    template < class task_type, class TMemInterface > struct base_sub_graph;

    /// <summary>
    /// Class base_task.
    /// </summary>
    /// <seealso cref="TMemInterface" />
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

        typedef guarded_vector< void *, TMemInterface > data_vector;

        /// <summary>
        /// Enum priority_selector
        /// </summary>
        enum priority_selector
        {
            realtime,
            high,
            normal,
            low,
            num_priority
        };

        /// <summary>
        /// Struct debug_container
        /// </summary>
        struct debug_container
        {
            /// <summary>
            /// Priorities to string.
            /// </summary>
            /// <param name="_priority">The priority.</param>
            /// <returns>const char *.</returns>
            const char *priority_to_string(priority_selector _priority) const;

            /// <summary>
            /// The task name
            /// </summary>
            string_type task_name;
            /// <summary>
            /// The dependent task names
            /// </summary>
            string_vector dependent_task_names;
        };

        /// <summary>
        /// Struct transient_container
        /// </summary>
        struct transient_container
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="base_task{TMemInterface}.transient_container"/> struct.
            /// </summary>
            transient_container(size_t _max_data_parallel_workload);
            /// <summary>
            /// Finalizes an instance of the <see cref="base_task{TMemInterface}.transient_container"/> class.
            /// </summary>
            ~transient_container();

            /// <summary>
            /// The start gate
            /// </summary>
            std::atomic_int64_t start_gate;
            /// <summary>
            /// The work queue
            /// </summary>
            work_queue_type *work_queue;
            /// <summary>
            /// The work allocator
            /// </summary>
            work_memory_allocator_type work_allocator;
            /// <summary>
            /// The number working
            /// </summary>
            std::atomic_int64_t num_working;
            /// <summary>
            /// Total time spent running all work functions in this task
            /// </summary>
            profile_time task_time;
            /// <summary>
            /// Total number of times work function was called
            /// </summary>
            std::atomic_int64_t num_runned;
            /// <summary>
            /// Total number of times work function was called
            /// </summary>
            data_vector data_workload;
        };

        /// <summary>
        /// Struct persistent_container
        /// </summary>
        struct persistent_container
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="base_task{TMemInterface}.persistent_container"/> struct.
            /// </summary>
            persistent_container();
            /// <summary>
            /// Finalizes an instance of the <see cref="base_task{TMemInterface}.persistent_container"/> class.
            /// </summary>
            ~persistent_container();

            /// <summary>
            /// The task priority
            /// </summary>
            priority_selector task_priority;
            /// <summary>
            /// The parent tasks
            /// </summary>
            task_vector parent_tasks;
            /// <summary>
            /// The dependent tasks
            /// </summary>
            task_vector dependent_tasks;
            /// <summary>
            /// The kick tasks
            /// </summary>
            task_vector kick_tasks;
            /// <summary>
            /// The sub graph
            /// </summary>
            sub_graph_type *sub_graph;
            /// <summary>
            /// The rank
            /// </summary>
            rank_type rank;
            /// <summary>
            /// The thread affinity
            /// </summary>
            int64_t thread_affinity;
            /// <summary>
            /// The task work
            /// </summary>
            task_work_vector task_work;
        };

        /// <summary>
        /// Initializes a new instance of the <see cref="base_task"/> class.
        /// </summary>
        /// <param name="_task_graph">The task graph.</param>
        base_task(task_graph_type &_task_graph, size_t _max_data_parallel_workload = 0);
        /// <summary>
        /// Finalizes an instance of the <see cref="base_task"/> class.
        /// </summary>
        ~base_task();
        /// <summary>
        /// Sets the thread affinity.
        /// </summary>
        /// <param name="_mask">The mask.</param>
        void set_thread_affinity(thread_mask_int_t _mask);
        /// <summary>
        /// Sets the thread exclusion.
        /// </summary>
        /// <param name="_mask">The mask.</param>
        void set_thread_exclusion(thread_mask_int_t _mask);
        /// <summary>
        /// Sets the number workers.
        /// </summary>
        /// <param name="_num_workers">The number workers.</param>
        void set_num_workers(thread_num_t _num_workers);
        /// <summary>
        /// Sets the number workers.
        /// </summary>
        /// <param name="_percentage_workers">The percentage workers.</param>
        void set_num_workers(percentage_t _percentage_workers);
        /// <summary>
        /// Finalizes this instance.
        /// </summary>
        void finalize();
        /// <summary>
        /// Kicks the dependent tasks.
        /// </summary>
        void kick_dependent_tasks();
        /// <summary>
        /// Adds the task parallel work.
        /// </summary>
        /// <param name="_work_function">The work function.</param>
        /// <returns>bool.</returns>
        bool add_task_parallel_work(function_type _work_function);
        /// <summary>
        /// Operator()s this instance.
        /// </summary>
        /// <returns>bool.</returns>
        bool operator()();
        /// <summary>
        /// Links the task.
        /// </summary>
        /// <param name="_next_task">The next task.</param>
        /// <returns>bool.</returns>
        bool link_task(task_type *_next_task);

        /// <summary>
        /// The debug
        /// </summary>
        debug_container debug;
        /// <summary>
        /// The transient
        /// </summary>
        transient_container transient;
        /// <summary>
        /// The persistent
        /// </summary>
        persistent_container persistent;
        /// <summary>
        /// The task graph
        /// </summary>
        task_graph_type &task_graph;

        /// <summary>
        /// The add task parallel work detector
        /// </summary>
        thread_unsafe_access_storage add_task_parallel_work_detector;

    private:
        /// <summary>
        /// Calls the working function internally
        /// </summary>
        /// <returns>bool.</returns>
        void run_internal(function_type* _work_function);
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
    base_task< TMemInterface >::transient_container::transient_container(size_t _max_data_parallel_workload)
        : work_queue(nullptr)
        , num_working(0)
        , task_time(0ms)
        , data_workload(_max_data_parallel_workload)
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
            instrument< void, task_type, void (task_type::*)(function_type*) >(transient.task_time, this, &task_type::run_internal, work_function);
            //(*work_function)();
            ++transient.num_runned;
            return true;
        }
        return false;
    }

    template < class TMemInterface > void base_task< TMemInterface >::run_internal(function_type* _work_function)
    {
        (*_work_function)();
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
    base_task< TMemInterface >::base_task(task_graph_type &_task_graph, size_t _max_data_parallel_workload)
        : task_graph(_task_graph)
        , transient(_max_data_parallel_workload)
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