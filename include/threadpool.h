#pragma once

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>

#include "containers.h"
#include "meta.h"
#include "profile.h"
#include "globals.h"

namespace task_scheduler {

    template <class TMemInterface>
    class base_task;
    template <class TMemInterface>
    class base_task_graph;
    template <class TMemInterface>
    class base_thread_pool;
    template <class TMemInterface>
    struct base_thread;

    template <class TMemInterface>
    class base_thread_pool {
        typedef base_thread<TMemInterface> thread_type;
        typedef base_task_graph<TMemInterface> task_graph_type;
        typedef base_thread_pool<TMemInterface> thread_pool;
        typedef typename task_graph_type::task_type task_type;
        typedef typename task_graph_type::task_queue_type task_queue_type;
        typedef typename task_graph_type::task_memory_allocator_type task_memory_allocator_type;
        typedef typename thread_type::thread_index_type thread_index_type;

    public:
        enum state_selector {
            run = 0,
            request_pause,
            request_stop
        };

        struct setup_container {
            std::mutex signal;
            std::condition_variable radio;
            std::atomic_uint32_t thread_sync;
            std::atomic<state_selector> request_exit;
        };

    public:
        base_thread_pool(thread_num_t _num_threads = max_num_threads);
        void start(task_graph_type& task_graph);
        void stop();
        void wake_up(thread_num_t num_threads_to_wake_up = max_num_threads);
        thread_type* get_current_thread();

        setup_container setup;
        thread_num_t num_threads;
        task_graph_type* task_graph;
        thread_type* threads[max_num_threads];
        task_memory_allocator_type task_memory_allocator;
        std::atomic<uint32_t> num_working;

        optimization std::atomic<typename task_type::rank_type> queue_rank[task_type::num_priority][max_num_threads];
    };

    template <class TMemInterface>
    base_thread_pool<TMemInterface>::base_thread_pool(thread_num_t _num_threads)
        : num_threads(std::min(std::min(static_cast<thread_num_t>(std::thread::hardware_concurrency()), max_num_threads), _num_threads))
        , task_graph(nullptr)
    {
        memset(threads, 0, sizeof(threads));
        for(auto& priority_queue : queue_rank)
        {
            for (auto& rank : priority_queue)
            {
                rank.store(0);
            }
        }
    }

    template <class TMemInterface>
    void base_thread_pool<TMemInterface>::start(task_graph_type& _task_graph)
    {
        task_graph = &_task_graph;
        setup.thread_sync.store(uint32_t(num_threads));

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++) {
            threads[thread_idx] = thread_type::create_thread(this);
        }

        //Wait until all threads are started
        while (setup.thread_sync != 0) {
            std::unique_lock<std::mutex> signal(setup.signal);
            setup.radio.wait(signal);
        }

        //kick all sleeping threads
        wake_up();
    }

    template <class TMemInterface>
    void base_thread_pool<TMemInterface>::stop()
    {
        setup.thread_sync = (uint32_t)task_graph->persistent.sub_graphs.size();
        setup.request_exit.store(request_pause);

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++) {
            threads[thread_idx]->join();
        }

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++) {
            delete threads[thread_idx];
        }

        memset(threads, 0, sizeof(threads));
    }

    template <class TMemInterface>
    void base_thread_pool<TMemInterface>::wake_up(thread_num_t _num_threads_to_wake_up)
    {
        _num_threads_to_wake_up = std::min(num_threads, _num_threads_to_wake_up);
        reduce_starvation(always_different_thread_woken_up_first) static thread_index_type next_thread_index(this,0);
        for (uint32_t iterations = 0; iterations < _num_threads_to_wake_up; ++next_thread_index, ++iterations) {
            threads[next_thread_index]->wake_up();
        }
        reduce_starvation(always_different_thread_woken_up_first) ++next_thread_index;
    }

    template <class TMemInterface>
    typename base_thread_pool<TMemInterface>::thread_type* base_thread_pool<TMemInterface>::get_current_thread()
    {
        return task_scheduler::get_current_thread<typename thread_pool::thread_type>();
    }

};