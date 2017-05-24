// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="thread.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <condition_variable>
#include <iomanip>

#include "containers.h"
#include "globals.h"
#include "print.h"
#include "profile.h"
#include "concurrency.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    template < class TMemInterface > class base_task;
    template < class TMemInterface > class base_task_graph;
    template < class TMemInterface > class base_thread_pool;

    /// <summary>
    /// Struct base_thread
    /// </summary>
    template < class TMemInterface > struct base_thread : public TMemInterface
    {
        typedef base_task_graph< TMemInterface > task_graph_type;
        typedef typename base_task< TMemInterface >::task_type task_type;
        typedef typename task_graph_type::task_queue_type task_queue_type;
        typedef base_thread< TMemInterface > thread_type;
        typedef base_thread_pool< TMemInterface > thread_pool;
        typedef typename task_graph_type::task_memory_allocator_type task_memory_allocator_type;
        typedef thread_index_t< TMemInterface > thread_index_type;

        /// <summary>
        /// Initializes a new instance of the <see cref="base_thread{TMemInterface}"/> struct.
        /// </summary>
        /// <param name="_thread_index">Index of the thread.</param>
        /// <param name="_pool">The pool.</param>
        base_thread(thread_num_t _thread_index, thread_pool *_pool);
        /// <summary>
        /// Finalizes an instance of the <see cref="base_thread{TMemInterface}"/> class.
        /// </summary>
        ~base_thread();

        /// <summary>
        /// Creates the thread.
        /// </summary>
        /// <param name="_pool">The pool.</param>
        /// <returns>thread_type *.</returns>
        static thread_type *create_thread(thread_pool *_pool);

        /// <summary>
        /// Sleeps the specified wake up.
        /// </summary>
        /// <param name="_wake_up">The wake up.</param>
        void sleep(bool (thread_type::*_wake_up)());
        /// <summary>
        /// Wakes up.
        /// </summary>
        void wake_up();
        /// <summary>
        /// Joins this instance.
        /// </summary>
        void join();

        task_queue_type *task_queue[task_type::num_priority];
        /// <summary>
        /// The task queue
        /// </summary>
        thread_index_type thread_index;
        /// <summary>
        /// The thread identifier
        /// </summary>
        std::thread::id thread_id;
        /// <summary>
        /// The task thread
        /// </summary>
        std::thread task_thread;
        /// <summary>
        /// The allocator
        /// </summary>
        task_memory_allocator_type allocator;

        friend class std::thread;
        template < class TMemInterface > friend class base_thread_pool;

      private:
          /// <summary>
          /// Initializes this instance.
          /// </summary>
          void init();
          /// <summary>
          /// Starts this thread
          /// </summary>
          void start();
          /// <summary>
          /// Runs this instance.
          /// </summary>
          void run();
          /// <summary>
          /// Determines whether [is task available].
          /// </summary>
          /// <returns>bool.</returns>
          bool is_task_available();
          /// <summary>
          /// Gets the task.
          /// </summary>
          /// <returns>task_type *.</returns>
          task_type *get_task();

          /// <summary>
          /// The pool
          /// </summary>
          thread_pool &pool;
          /// <summary>
          /// The signal
          /// </summary>
          std::mutex signal;
          /// <summary>
          /// The radio
          /// </summary>
          std::condition_variable radio;

          event sync_point;

          alarm execution;
    };

    template < class TMemInterface >
    base_thread< TMemInterface >::base_thread(thread_num_t _thread_index, thread_pool *_pool)
        : thread_index(_pool, _thread_index)
        , pool(*_pool)
    {
        for (auto &queue : task_queue)
        {
            queue = new task_queue_type(&allocator);
        }

        task_thread = std::thread([&] {
            init();
            run();
        });
    }

    template < class TMemInterface > base_thread< TMemInterface >::~base_thread()
    {
        for (auto &queue : task_queue)
        {
            delete queue;
            queue = nullptr;
        }
    }

    template < class TMemInterface >
    base_thread< TMemInterface > *base_thread< TMemInterface >::create_thread(thread_pool *_pool)
    {
        static thread_num_t next_thread_num = 0;
        return new thread_type(next_thread_num++, _pool);
    }

    template < class TMemInterface > void base_thread< TMemInterface >::init()
    {
        thread_id = std::this_thread::get_id();
        current_thread = this;
        tostringstream stringStream;
        stringStream << uint32_t(thread_index);
        thread_name = stringStream.str();
        //profile::thread::set_name(thread_name.c_str());

        // Signal thread_type has started
        --pool.setup.thread_sync;
        pool.setup.radio.notify_one();

        // wake_up when all threads have started
        sync_point.wait();
    }

    template < class TMemInterface > void base_thread< TMemInterface >::start()
    {
        sync_point.signal();
    }

    template < class TMemInterface > void base_thread< TMemInterface >::sleep(bool (thread_type::*_wake_up)())
    {
        execution.sleep(
            [&]()->bool
            {
                return ((this->*_wake_up)() || pool.setup.request_exit == thread_pool::request_stop);
            }
        );
    }

    template < class TMemInterface > void base_thread< TMemInterface >::wake_up()
    {
        execution.wake_up();
    }

    template < class TMemInterface > void base_thread< TMemInterface >::join() { task_thread.join(); }

    template < class TMemInterface > bool base_thread< TMemInterface >::is_task_available()
    {
        for (auto queue : task_queue)
        {
            if (!queue->empty())
            {
                return true;
            }
        }

        return pool.task_graph->is_task_available();
    }

    template < class TMemInterface > void base_thread< TMemInterface >::run()
    {
        using namespace std;
        profile::time scheduling(0ms), sleeping(0ms), working(0ms);

        ts_print("ready");

        while (pool.setup.request_exit != thread_pool::request_stop)
        {
            // Steal task_type
            task_type *run_task = profile::instrument< task_type *, thread_type, task_type *(thread_type::*)() >(
                scheduling, this, &thread_type::get_task);

            if (run_task)
            {
                // Run task_type
                profile::time task_time(0ms);
                ++pool.num_working;
                ++run_task->transient.num_working;
                while (
                    profile::instrument< bool, task_type, bool (task_type::*)() >(task_time, run_task, &task_type::operator()))
                {
                };
                --run_task->transient.num_working;
                --pool.num_working;
                ts_print("run " << run_task->debug.task_name << "("
                                << chrono::duration_cast< chrono::milliseconds >(task_time).count() << "ms)");
                working += task_time;

                if (run_task->transient.num_working == 0)
                {
                    // Donate More Tasks
                    profile::instrument< void, task_type, void (task_type::*)() >(scheduling, run_task,
                                                                         &task_type::kick_dependent_tasks);
                }
            }
            else if (!is_task_available())
            {
                // Go to sleep if there is no task to run
                profile::instrument< void, thread_type, void (thread_type::*)(bool (thread_type::*)()) >(
                    sleeping, this, &thread_type::sleep, &thread_type::is_task_available);
            }
        };

        assert(!is_task_available());

        auto scheduling_ms = std::chrono::duration_cast< std::chrono::milliseconds >(scheduling);
        auto sleeping_ms = std::chrono::duration_cast< std::chrono::milliseconds >(sleeping);
        auto working_ms = std::chrono::duration_cast< std::chrono::milliseconds >(working);
        auto scheduling_ratio = double(working.count() / (scheduling.count() == 0 ? 1 : scheduling.count()));
        ts_print("Complete, Scheduling Overhead=" << scheduling_ms.count() << "ms, sleep Time=" << sleeping_ms.count()
                                                  << "ms, Work Time=" << working_ms.count()
                                                  << "ms, Work/Schedule Ratio=" << fixed << setprecision(0)
                                                  << scheduling_ratio);
    }

    template < class TMemInterface >
    typename base_thread< TMemInterface >::task_type *base_thread< TMemInterface >::get_task()
    {
        task_type *next_task = nullptr;
        for (uint32_t priority = 0; priority < task_type::num_priority; priority++)
        {
            // Try to get a task from the thread queue
            if (task_queue[priority]->pop_front(next_task))
            {
                break;
            }

            // Try to get a new manually scheduled task from the global queue
            next_task = pool.task_graph->dequeue_task(priority);
            if (next_task)
            {
                pool.queue_rank[priority][thread_index].fetch_add(next_task->persistent.rank);
                break;
            }

            // Try to steal task from other threads, starting from the previous thread
            // In practice the spinning of the lock free queue, in a way locks the current thread we are trying to steal
            // from
            // Disabling thread affinities will make the stealing much more efficient
            thread_index_type current_thread_index = thread_index - 1;
            do
            {
                task_type *stolen_task = nullptr;
                std::vector< task_type * > temporary_queue;
                bool touched_thread = false;
                do
                {
                    if (pool.threads[current_thread_index]->task_queue[priority]->pop_front(stolen_task))
                    {
                        touched_thread = true;
                        if (current_thread_index.is_set(stolen_task->persistent.thread_affinity))
                        {
                            // Steal task
                            next_task = stolen_task;
                            ts_print("stole " << next_task->debug.task_name << " <- "
                                              << uint32_t(current_thread_index));
                            break;
                        }
                        else
                        {
                            // Steal wrong task
                            temporary_queue.push_back(stolen_task);
                        }
                    }
                } while (!pool.threads[current_thread_index]->task_queue[priority]->empty());

                for (auto task_ptr : temporary_queue)
                {
                    // Return tasks
                    pool.threads[current_thread_index]->task_queue[priority]->push_back(task_ptr);
                }

                // We have to wakeup the thread as long as its task queue is touched
                // There could be task that was stolen and returned, but the thread went to sleep during the theft and
                // before the return
                if (touched_thread)
                {
                    pool.threads[current_thread_index]->wake_up();
                }

                if (next_task)
                {
                    break;
                }

                --current_thread_index;
            } while (current_thread_index != thread_index);

            if (next_task)
            {
                break;
            }
        }

        return next_task;
    }
};