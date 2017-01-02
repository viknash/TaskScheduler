// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="print.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#include "globals.h"
#include "platform.h"
#include "utils.h"

#if !defined(TASK_SCHEDULER_DEBUG)
#error("TASK_SCHEDULER_DEBUG is not defined")
#endif // !defined(TASK_SCHEDULER_DEBUG)

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

#if defined(TASK_SCHEDULER_DEBUG)
    /// <summary>
    /// Struct out_t
    /// </summary>
    struct out_t
    {
        /// <summary>
        /// Operators the specified x.
        /// </summary>
        /// <param name="x">The x.</param>
        /// <returns>task_scheduler.out_t &.</returns>
        template < typename T > out_t &operator<<(T &&x)
        {
            buffer << x;
            return *this;
        };

        /// <summary>
        /// Initializes a new instance of the <see cref="out_t"/> struct.
        /// </summary>
        out_t() { buffer << thread_name << "> "; }

        /// <summary>
        /// Finalizes an instance of the <see cref="out_t"/> class.
        /// </summary>
        ~out_t()
        {
            std::lock_guard< std::mutex > lk(globals.io_mutex);
            ts_windows_only(SetConsoleTextAttribute(globals.console_handle, get_thread_number()););
            std::cout << buffer.str() << std::endl;
        }

        /// <summary>
        /// The buffer
        /// </summary>
        std::ostringstream buffer;
    };
#else  // defined(TASK_SCHEDULER_DEBUG)
    /// <summary>
    /// Struct out_t
    /// </summary>
    struct out_t
    {
        /// <summary>
        /// Operators the specified x.
        /// </summary>
        /// <param name="x">The x.</param>
        /// <returns>task_scheduler.out_t &.</returns>
        template < typename T > out_t &operator<<(T &&x) { return *this; };
    };
#endif // defined(TASK_SCHEDULER_DEBUG)

#define task_scheduler_static_data()                                                                                   \
    namespace task_scheduler                                                                                           \
    {                                                                                                                  \
        static_data_t globals;                                                                                         \
    };

#define ts_print_internal(arg)                                                                                         \
    out_t arg;                                                                                                         \
    arg

#define ts_print(x)                                                                                                    \
    {                                                                                                                  \
        ts_print_internal(ts_unique_variable(printout)) << x;                                                          \
    }
};