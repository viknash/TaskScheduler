// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="utils.h" >
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
#include <cassert>

#include "types.h"


#if !defined(TASK_SCHEDULER_DEBUG)
#error("TASK_SCHEDULER_DEBUG is not defined")
#endif

#if !defined(TASK_SCHEDULER_ASSERT)
#error("TASK_SCHEDULER_ASSERT is not defined")
#endif

#if TASK_SCHEDULER_DEBUG == 0
#define ts_debug_only(x)
#else
#define ts_debug_only(x) x
#endif

#if TASK_SCHEDULER_ASSERT == 0
#define ts_assert(x)
#else
#define ts_assert(x) assert(x)
#endif

#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_ITT
#include "ittnotify.h"
#define ts_itt(x) x
#else
#define ts_itt(x)
#endif

#define ts_join_string(arg0, arg1) ts_do_join(arg0, arg1)
#define ts_do_join(arg0, arg1) arg0##arg1

#define ts_unique_variable(basename) ts_join_string(basename, __COUNTER__)

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// Creates the mask 64.
    /// </summary>
    /// <returns>thread_mask_int_t.</returns>
    inline thread_mask_int_t create_mask_64() { return 0; }

    /// <summary>
    /// Creates the mask 64.
    /// </summary>
    /// <param name="first">The first.</param>
    /// <param name="...args">The ...args.</param>
    /// <returns>thread_mask_int_t.</returns>
    template < typename T, typename... Args > thread_mask_int_t create_mask_64(T first, Args... args)
    {
        return create_mask_64(args...) | 1ull << first;
    }

    /// <summary>
    /// Class unsafe_multi_threaded_access_detector.
    /// </summary>
    template < class T > class unsafe_multi_threaded_access_detector
    {

      public:
          /// <summary>
          /// Initializes a new instance of the <see cref="unsafe_multi_threaded_access_detector"/> class.
          /// </summary>
          unsafe_multi_threaded_access_detector()
            : previous_thread_id(0)
        {
        }

        /// <summary>
        /// Enters the specified storage.
        /// </summary>
        /// <param name="storage">The storage.</param>
        /// <returns>bool.</returns>
        bool enter(T &storage)
        {
            int64_t new_thread_id = std::hash< std::thread::id >()(std::this_thread::get_id());
            previous_thread_id = storage.last_thread_id.exchange(new_thread_id);
            bool success = previous_thread_id == 0 || previous_thread_id == new_thread_id;
            ts_assert(success);
            return success;
        }

        /// <summary>
        /// Exits the specified storage.
        /// </summary>
        /// <param name="storage">The storage.</param>
        /// <returns>bool.</returns>
        bool exit(T &storage)
        {
            int64_t stored_thread_id = storage.last_thread_id.exchange(previous_thread_id);
            int64_t current_thread_id = std::hash< std::thread::id >()(std::this_thread::get_id());
            bool success = stored_thread_id == current_thread_id || stored_thread_id == 0;
            ts_assert(success);
            return success;
        }

      private:
          /// <summary>
          /// The previous thread identifier
          /// </summary>
          std::atomic_int64_t previous_thread_id;
    };

    /// <summary>
    /// Class scoped_enter_exit.
    /// </summary>
    /// <seealso cref="T" />
    template < typename T, typename TParam > class scoped_enter_exit : public T
    {
      public:
          /// <summary>
          /// Initializes a new instance of the <see cref="scoped_enter_exit"/> class.
          /// </summary>
          /// <param name="_param">The parameter.</param>
          scoped_enter_exit(TParam &_param)
            : param(_param)
        {
            this->enter(param);
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="scoped_enter_exit"/> class.
        /// </summary>
        ~scoped_enter_exit() { this->exit(param); }

      private:
          /// <summary>
          /// The parameter
          /// </summary>
          TParam &param;
    };

    /// <summary>
    /// Struct thread_unsafe_access_storage
    /// </summary>
    struct thread_unsafe_access_storage
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="thread_unsafe_access_storage"/> struct.
        /// </summary>
        thread_unsafe_access_storage()
            : last_thread_id(0)
        {
        }
        /// <summary>
        /// The last thread identifier
        /// </summary>
        std::atomic_int64_t last_thread_id;
    };

    typedef scoped_enter_exit< unsafe_multi_threaded_access_detector< thread_unsafe_access_storage >,
                               thread_unsafe_access_storage >
        thread_unsafe_access_guard;

    template<class TInterface>
    TInterface* get()
    {
        static TInterface* system;
        if (!system)
        {
            system = TInterface::instance();
        }
        return system;
    }

    template<class TInterface>
    TInterface* create()
    {
        return TInterface::allocate();
    }

    template<class TInterface>
    void destroy(TInterface* _interface)
    {
        TInterface::deallocate(_interface);
    }
};