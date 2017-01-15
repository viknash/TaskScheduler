// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="threadpool.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>

#include "containers.h"
#include "globals.h"
#include "meta.h"
#include "profile.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    template < class TMemInterface > class base_task;
    template < class TMemInterface > class base_task_graph;
    template < class TMemInterface > class base_thread_pool;
    template < class TMemInterface > struct base_thread;

    /// <summary>
    /// Class base_thread_pool.
    /// </summary>
    template < class TMemInterface > class base_thread_pool
    {
        typedef base_thread< TMemInterface > thread_type;
        typedef base_task_graph< TMemInterface > task_graph_type;
        typedef base_thread_pool< TMemInterface > thread_pool;
        typedef typename task_graph_type::task_type task_type;
        typedef typename task_graph_type::task_queue_type task_queue_type;
        typedef typename task_graph_type::task_memory_allocator_type task_memory_allocator_type;
        typedef typename thread_type::thread_index_type thread_index_type;

      public:
          /// <summary>
          /// Enum state_selector
          /// </summary>
          enum state_selector
        {
            run = 0,
            request_pause,
            request_stop
        };

          /// <summary>
          /// Struct setup_container
          /// </summary>
          struct setup_container
        {
              /// <summary>
              /// The signal
              /// </summary>
              std::mutex signal;
              /// <summary>
              /// The radio
              /// </summary>
              std::condition_variable radio;
              /// <summary>
              /// The thread synchronize
              /// </summary>
              std::atomic_uint32_t thread_sync;
              /// <summary>
              /// The request exit
              /// </summary>
              std::atomic< state_selector > request_exit;
        };

      public:
          /// <summary>
          /// Initializes a new instance of the <see cref="base_thread_pool"/> class.
          /// </summary>
          /// <param name="_num_threads">The number threads.</param>
          base_thread_pool(thread_num_t _num_threads = max_num_threads);
          /// <summary>
          /// Starts the specified task graph.
          /// </summary>
          /// <param name="task_graph">The task graph.</param>
          void start(task_graph_type &task_graph);
          /// <summary>
          /// Stops this instance.
          /// </summary>
          void stop();
          /// <summary>
          /// Wakes up.
          /// </summary>
          /// <param name="num_threads_to_wake_up">The number threads to wake up.</param>
          void wake_up(thread_num_t num_threads_to_wake_up = max_num_threads);
          /// <summary>
          /// Gets the current thread.
          /// </summary>
          /// <returns>thread_type *.</returns>
          thread_type *get_current_thread();

          /// <summary>
          /// The setup
          /// </summary>
          setup_container setup;
          /// <summary>
          /// The number threads
          /// </summary>
          thread_num_t num_threads;
          /// <summary>
          /// The task graph
          /// </summary>
          task_graph_type *task_graph;
          thread_type *threads[max_num_threads];
          /// <summary>
          /// The threads
          /// </summary>
          task_memory_allocator_type task_memory_allocator;
          /// <summary>
          /// The number working
          /// </summary>
          std::atomic< uint32_t > num_working;

        optimization std::atomic< typename task_type::rank_type > queue_rank[task_type::num_priority][max_num_threads];
    };

    template < class TMemInterface >
    base_thread_pool< TMemInterface >::base_thread_pool(thread_num_t _num_threads)
        : num_threads(
              std::min(std::min(static_cast< thread_num_t >(std::thread::hardware_concurrency()), max_num_threads),
                       _num_threads))
        , task_graph(nullptr)
    {
        memset(threads, 0, sizeof(threads));
        for (auto &priority_queue : queue_rank)
        {
            for (auto &rank : priority_queue)
            {
                rank.store(0);
            }
        }
    }

    template < class TMemInterface > void base_thread_pool< TMemInterface >::start(task_graph_type &_task_graph)
    {
        task_graph = &_task_graph;
        setup.thread_sync.store(uint32_t(num_threads));

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++)
        {
            threads[thread_idx] = thread_type::create_thread(this);
        }

        // Wait until all threads are started
        while (setup.thread_sync != 0)
        {
            std::unique_lock< std::mutex > signal(setup.signal);
            setup.radio.wait(signal);
        }

        // kick all sleeping threads
        for (uint32_t iterations = 0; iterations < num_threads; ++iterations)
        {
            threads[iterations]->start();
        }
    }

    template < class TMemInterface > void base_thread_pool< TMemInterface >::stop()
    {
        setup.thread_sync = (uint32_t)task_graph->persistent.sub_graphs.size();
        setup.request_exit.store(request_pause);

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++)
        {
            threads[thread_idx]->join();
        }

        for (uint32_t thread_idx = 0; thread_idx < num_threads; thread_idx++)
        {
            delete threads[thread_idx];
        }

        memset(threads, 0, sizeof(threads));
    }

    template < class TMemInterface >
    void base_thread_pool< TMemInterface >::wake_up(thread_num_t _num_threads_to_wake_up)
    {
        _num_threads_to_wake_up = std::min(num_threads, _num_threads_to_wake_up);
        reduce_starvation(always_different_thread_woken_up_first) static thread_index_type next_thread_index(this, 0);
        for (uint32_t iterations = 0; iterations < _num_threads_to_wake_up; ++next_thread_index, ++iterations)
        {
            threads[next_thread_index]->wake_up();
        }
        reduce_starvation(always_different_thread_woken_up_first)++ next_thread_index;
    }

    template < class TMemInterface >
    typename base_thread_pool< TMemInterface >::thread_type *base_thread_pool< TMemInterface >::get_current_thread()
    {
        return task_scheduler::get_current_thread< typename thread_pool::thread_type >();
    }
};