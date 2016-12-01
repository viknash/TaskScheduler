#pragma once

#include <atomic>

#include "meta.h"
#include "memory.h"

namespace task_scheduler {

    template <class TMemInterface>
    class base_task_graph;
    template <class TMemInterface>
    class base_thread_pool;
    template <class TMemInterface>
    struct base_thread;
    template <class task_type, class TMemInterface>
    struct base_sub_graph;

    template <class TMemInterface>
    class base_task : public TMemInterface {
    public:
        typedef base_task<TMemInterface> task_type;
        typedef base_thread<TMemInterface> thread_type;
        typedef base_task_graph<TMemInterface> task_graph_type;
        typedef base_sub_graph<task_type, TMemInterface> sub_graph_type;
        typedef std::basic_string<char, std::char_traits<char>, stl_allocator<char, TMemInterface>> string_type;
        typedef std::vector<string_type, stl_allocator<string_type, TMemInterface>> string_vector;
        typedef std::vector<task_type*, stl_allocator<task_type*, TMemInterface>> task_vector;
        typedef base_thread_pool<TMemInterface> thread_pool;
        typedef std::function<void()> function_type;
        typedef typename int64_t rank_type;

        enum priority_selector {
            REALTIME,
            HIGH,
            NORMAL,
            LOW,
            NUM_PRIORITY
        };

        struct debug_container {
            const char* priority_to_string(priority_selector _priority) const;

            string_type task_name;
            string_vector dependent_task_names;
        };

        struct transient_container {
            std::atomic_int64_t start_gate;
        };

        struct persistent_container {
            persistent_container();

            priority_selector task_priority;
            task_vector parent_tasks;
            task_vector dependent_tasks;
            task_vector kick_tasks;
            function_type run_functor;
            sub_graph_type* sub_graph;
            rank_type rank;
            int64_t thread_affinity;
        };

        void set_thread_affinity(uint64_t mask);
        void set_thread_exclusion(uint64_t mask);
        base_task(task_graph_type& _task_graph);
        void kick_dependent_tasks();
        void operator()();
        bool link_task(task_type* _next_task);

        debug_container debug;
        transient_container transient;
        persistent_container persistent;
        task_graph_type& task_graph;
    };

    template <class TMemInterface>
    const char* base_task<TMemInterface>::debug_container::priority_to_string(priority_selector priority) const
    {
        static const char* priority_to_string[] = {
            "REALTIME",
            "HIGH",
            "NORMAL",
            "LOW"
        };

        return priority_to_string[uint32_t(priority)];
    }

    template <class TMemInterface>
    base_task<TMemInterface>::persistent_container::persistent_container()
        : task_priority(NORMAL)
        , sub_graph(nullptr)
        , rank(0)
        , thread_affinity(0)
    {
    }

    template <class TMemInterface>
    void base_task<TMemInterface>::operator()()
    {
        persistent.run_functor();
    }

    template <class TMemInterface>
    void base_task<TMemInterface>::set_thread_affinity(uint64_t _mask)
    {
        task_graph.set_task_thread_affinity(this, _mask);
    }

    template <class TMemInterface>
    void base_task<TMemInterface>::set_thread_exclusion(uint64_t _mask)
    {
        task_graph.set_task_thread_exclusion(this, _mask);
    }

    template <class TMemInterface>
    base_task<TMemInterface>::base_task(task_graph_type& _task_graph)
        : task_graph(_task_graph)
    {
    }

    template <class TMemInterface>
    void base_task<TMemInterface>::kick_dependent_tasks()
    {
        //Reduce queue rank of queue that the current task is running on
        task_graph.pool.queue_rank[persistent.task_priority][task_graph.pool.current_thread->thread_index].fetch_sub(persistent.rank);

        //Queue dependent tasks only when their start gates are 0
        //i.e. all parent tasks have been executed

        //If we are scheduling many tasks at once search for the next best ranked queue, starting from just after the queue that was just scheduled
        reduce_starvation(new_search_index) uint32_t best_search_index = task_graph.pool.current_thread->thread_index;

        for (auto dependent_task : persistent.dependent_tasks) {
            if (--dependent_task->transient.start_gate == 0) {
                //Find lowest ranking queue, aka best queue and increment its rank with dependent task rank
                uint32_t current_thread_index = 0;
                thread_type* best_thread = nullptr;
                rank_type best_rank = std::numeric_limits<rank_type>::max();
                do {
                    best_thread = nullptr;
                    best_rank = std::numeric_limits<rank_type>::max();
                    reduce_starvation(new_search_index) current_thread_index = best_search_index;
                    while ((current_thread_index = (current_thread_index + 1) % task_graph.pool.num_threads) != best_search_index) {
                        if (!(dependent_task->persistent.thread_affinity & 1ull << current_thread_index))
                            continue; //Skip threads the task should not run on

                        int64_t current_thread_rank = task_graph.pool.queue_rank[dependent_task->persistent.task_priority][current_thread_index].load();
                        if (current_thread_rank < best_rank) {
                            best_rank = current_thread_rank;
                            best_thread = task_graph.pool.threads[current_thread_index];
                        }
                    }
                } while (!task_graph.pool.queue_rank[dependent_task->persistent.task_priority][best_thread->thread_index].compare_exchange_weak(best_rank, best_rank + dependent_task->persistent.rank));

                //Push task into the best queue
                uint32_t dependent_task_priority = dependent_task->persistent.task_priority;
                do {
                } while (!best_thread->task_queue[dependent_task_priority]->push_back(dependent_task) && ++dependent_task_priority < task_type::NUM_PRIORITY);
                assert(dependent_task_priority < task_type::NUM_PRIORITY);

                //Wake up thread if its sleeping
                best_thread->wake_up();

                reduce_starvation(new_search_index) best_search_index = best_thread->thread_index;
            }
        }

        //Stop kicking tasks when a request to pause has been received
        //If all tail kickers have paused, then request the threads to stop
        if (persistent.kick_tasks.size() && task_graph.pool.setup.request_exit == thread_pool::request_pause) {
            --task_graph.pool.setup.thread_sync;
            if (!task_graph.pool.setup.thread_sync) {
                task_graph.pool.setup.request_exit.store(thread_pool::request_stop);
                task_graph.pool.wake_up();
            }
            return;
        }

        //Only Tail task_type Nodes should have kick tasks
        //kick tasks are Head Tasks for the next frame
        bool initializedSubGraph = false;
        for (auto kick_task : persistent.kick_tasks) {
            if (!initializedSubGraph) {
                task_graph.initialize(kick_task->persistent.sub_graph);
                initializedSubGraph = true;
            }
            uint64_t start_gate = kick_task->transient.start_gate.load();
            assert(start_gate == 0); start_gate;
            task_graph.queue_task(kick_task);
        }
    }

    template <class TMemInterface>
    bool base_task<TMemInterface>::link_task(task_type* _next_task)
    {
        return task_graph.link_task(this, _next_task);
    }

};