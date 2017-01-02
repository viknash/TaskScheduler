// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="atomics.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <cstdint>

#include "platform.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// The atomics namespace.
    /// </summary>
    namespace atomics
    {
        /// <summary>
        /// Increments the specified data.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <returns>int64_t.</returns>
        inline int64_t increment(volatile int64_t &_data) { return _InterlockedIncrement64(&_data); }

        /// <summary>
        /// Decrements the specified data.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <returns>int64_t.</returns>
        inline int64_t decrement(volatile int64_t &_data) { return _InterlockedDecrement64(&_data); }

        /// <summary>
        /// Increments the specified data.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <returns>int32_t.</returns>
        inline int32_t increment(volatile int32_t &_data)
        {
            return _InterlockedIncrement(reinterpret_cast< volatile long * >(&_data));
        }

        /// <summary>
        /// Decrements the specified data.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <returns>int32_t.</returns>
        inline int32_t decrement(volatile int32_t &_data)
        {
            return _InterlockedDecrement(reinterpret_cast< volatile long * >(&_data));
        }

        /// <summary>
        /// Compares the exchange weak.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <param name="_comperand">The comperand.</param>
        /// <param name="_value">The value.</param>
        /// <returns>int32_t.</returns>
        inline int32_t compare_exchange_weak(volatile int32_t &_data, int32_t _comperand, int32_t _value)
        {
            return _InterlockedCompareExchange(reinterpret_cast< volatile long * >(&_data), static_cast< long >(_value),
                                               static_cast< long >(_comperand));
        }

        /// <summary>
        /// Compares the exchange weak.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <param name="_comperand">The comperand.</param>
        /// <param name="_value">The value.</param>
        /// <returns>int64_t.</returns>
        inline int64_t compare_exchange_weak(volatile int64_t &_data, int64_t _comperand, int64_t _value)
        {
            return _InterlockedCompareExchange64(&_data, _value, _comperand);
        }

        /// <summary>
        /// Compares the exchange weak.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <param name="_comperand">The comperand.</param>
        /// <param name="_value">The value.</param>
        /// <returns>T *.</returns>
        template < class T > inline T *compare_exchange_weak(T *volatile &_data, T *_comperand, T *_value)
        {
            return reinterpret_cast< T * >(_InterlockedCompareExchangePointer(
                reinterpret_cast< void *volatile * >(&_data), reinterpret_cast< void * >(_value),
                reinterpret_cast< void * >(_comperand)));
        }

        /// <summary>
        /// Compares the exchange weak 128.
        /// </summary>
        /// <param name="_data">The data.</param>
        /// <param name="_comperand">The comperand.</param>
        /// <param name="_value_hi">The value hi.</param>
        /// <param name="_value_lo">The value lo.</param>
        /// <returns>bool.</returns>
        inline bool compare_exchange_weak_128(volatile int64_t _data[], int64_t _comperand[], int64_t _value_hi,
                                              int64_t _value_lo)
        {
            return _InterlockedCompareExchange128(_data, _value_hi, _value_lo, _comperand) == 1;
        }

        typedef int64_t type;
    };
};
