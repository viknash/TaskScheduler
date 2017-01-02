// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="globals.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>
#include <cstdint>
#include <thread>

#include "platform.h"
#include "types.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// The maximum number threads
    /// </summary>
    const thread_num_t max_num_threads = 64;

    /// <summary>
    /// Struct static_data_t
    /// </summary>
    struct static_data_t
    {
        /// <summary>
        /// The io mutex
        /// </summary>
        std::mutex io_mutex;
        ts_windows_only(HANDLE console_handle;);
        /// <summary>
        /// The next thread number
        /// </summary>
        std::atomic< thread_num_t > next_thread_number;

        /// <summary>
        /// Statics the data t.
        /// </summary>
        /// <returns>int.</returns>
        static_data_t()
            : next_thread_number(1)
        {
            ts_windows_only(console_handle = GetStdHandle(STD_OUTPUT_HANDLE););
        }
    };

    extern static_data_t globals;

    /// <summary>
    /// The thread name
    /// </summary>
    thread_local std::string thread_name;
    /// <summary>
    /// The thread unique number
    /// </summary>
    thread_local thread_num_t thread_unique_number;
    /// <summary>
    /// The current thread
    /// </summary>
    thread_local void *current_thread;

    /// <summary>
    /// Gets the thread number.
    /// </summary>
    /// <returns>uint8_t.</returns>
    inline uint8_t get_thread_number()
    {
        if (!thread_unique_number)
        {
            thread_unique_number = ++globals.next_thread_number;
        }
        return thread_unique_number;
    }

    /// <summary>
    /// Gets the current thread.
    /// </summary>
    /// <returns>T *.</returns>
    template < class T > T *get_current_thread() { return static_cast<T *>(current_thread); }

#define task_scheduler_static_data()                                                                                   \
    namespace task_scheduler                                                                                           \
    {                                                                                                                  \
        static_data_t globals;                                                                                         \
    };
}