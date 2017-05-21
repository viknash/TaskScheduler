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

#include "platform.h"
#include "globals.h"


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
            std::lock_guard< std::mutex > lk(get<globals>()->io_mutex);
            ts_windows_only(SetConsoleTextAttribute(get<globals>()->console_handle, get_thread_number()););
            tcout << buffer.str() << std::endl;
        }

        /// <summary>
        /// The buffer
        /// </summary>
        tostringstream buffer;
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

#define ts_print_internal(arg)                                                                                         \
    out_t arg;                                                                                                         \
    arg

#define ts_print(x)                                                                                                    \
    {                                                                                                                  \
        ts_print_internal(ts_unique_variable(printout)) << x;                                                          \
    }
};