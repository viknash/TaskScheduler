// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="profile.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <thread>


/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    typedef std::chrono::time_point< std::chrono::high_resolution_clock > profile_time_point;
    typedef std::chrono::high_resolution_clock profile_clock;
    typedef std::chrono::microseconds profile_time;

    /// <summary>
    /// Struct profile_timer
    /// </summary>
    struct profile_timer
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="profile_timer"/> struct.
        /// </summary>
        /// <param name="_elapsedTime">The elapsed time.</param>
        profile_timer(std::chrono::microseconds &_elapsedTime)
            : start(profile_clock::now())
            , elapsedTime(_elapsedTime)
        {
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="profile_timer"/> class.
        /// </summary>
        ~profile_timer()
        {
            elapsedTime += std::chrono::duration_cast< std::chrono::microseconds >(profile_clock::now() - start);
        }

        /// <summary>
        /// The start
        /// </summary>
        profile_time_point start;
        /// <summary>
        /// The elapsed time
        /// </summary>
        profile_time &elapsedTime;
    };

    /// <summary>
    /// Instruments the specified profile time.
    /// </summary>
    /// <param name="_profileTime">The profile time.</param>
    /// <param name="_classType">Type of the class.</param>
    /// <param name="_func">The function.</param>
    /// <param name="..._params">The ... parameters.</param>
    /// <returns>TReturnType.</returns>
    template < typename TReturnType, typename TClassType, typename TMemFunc, typename... TArgs >
    TReturnType instrument(profile_time &_profileTime, TClassType *_classType, TMemFunc _func, TArgs... _params)
    {
        profile_timer profile(_profileTime);
        return (_classType->*_func)(std::forward< TArgs >(_params)...);
    }

    class profile
    {
    public:
        ts_itt(typedef __itt_heap_function* handle;);
        const handle invalid_handle = nullptr;

        static handle heap_function_create(const tchar_t* _name, tchar_t* _domain)
        {
            handle hnd;
            hnd = ts_itt(&__itt_heap_function_create(_name, _domain););
            return hnd;
        }

        static void heap_allocate_begin(handle _heap, size_t _size, bool _initialized)
        {
            ts_itt(__itt_heap_allocate_begin(*_heap, _size, _initialized ? 1 : 0););
        }

        static void heap_allocate_end(handle _heap, void** _memory_allocation, size_t _size, bool _initialized)
        {
            ts_itt(heap_allocate_end(*_heap, _memory_allocation, _size, _initialized ? 1 : 0););
        }

    };
};