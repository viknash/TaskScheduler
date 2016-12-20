#pragma once

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>

#include "containers.h"
#include "meta.h"
#include "profile.h"

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
        typedef typename base_thread<TMemInterface> thread_type;
        typedef typename base_task_graph<TMemInterface> task_graph_type;
        typedef typename task_graph_type::task_type task_type;
        typedef typename task_graph_type::task_queue_type task_queue_type;
        typedef typename task_graph_type::task_memory_allocator_type task_memory_allocator_type;
        typedef typename base_thread_pool<TMemInterface> thread_pool;

    public:
        enum state_selector {
            run = 0,
            request_pause,
            request_stop
        };

        struct setup_container {
            std::mutex signal;
            std::condition_variable radio;
            std::atomic<uint32_t> thread_sync;
            std::atomic<state_selector> request_exit;
        };

    public:
        base_thread_pool(uint32_t _num_threads = MAX_NUM_THREADS);
        void start(task_graph_type& task_graph);
        void stop();
        void wake_up(uint8_t num_threads_to_wake_up = MAX_NUM_THREADS);

        static const uint32_t MAX_NUM_THREADS = 64;

        setup_container setup;
        uint8_t num_threads;
        task_graph_type* task_graph;
        thread_type* threads[MAX_NUM_THREADS];
        task_memory_allocator_type task_memory_allocator;
        std::atomic<uint32_t> num_working;

        optimization std::atomic<typename task_type::rank_type> queue_rank[task_type::NUM_PRIORITY][MAX_NUM_THREADS];

        thread_local static thread_type* current_thread;
    };

    template <class TMemInterface>
    base_thread_pool<TMemInterface>::base_thread_pool(uint32_t _num_threads)
        : num_threads(static_cast<uint8_t>(std::min(std::min(std::thread::hardware_concurrency(), MAX_NUM_THREADS), _num_threads)))
        , task_graph(nullptr)
    {
        memset(threads, 0, sizeof(threads));
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
            unique_lock<mutex> signal(setup.signal);
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
    void base_thread_pool<TMemInterface>::wake_up(uint8_t _num_threads_to_wake_up)
    {
        _num_threads_to_wake_up = min(num_threads, _num_threads_to_wake_up);
        reduce_starvation(always_different_thread_woken_up_first) static uint32_t next_thread_index = 0;
        for (uint32_t thread_idx = next_thread_index, iterations = 0; iterations < _num_threads_to_wake_up; thread_idx = (thread_idx + 1) % num_threads, iterations++) {
            threads[thread_idx]->wake_up();
        }
        reduce_starvation(always_different_thread_woken_up_first) next_thread_index = (next_thread_index + 1) % num_threads;
    }

};