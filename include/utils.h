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
#define ts_assert(x) ts_unused(x)
#define ts_always_assert()
#else
#define ts_assert(x) assert(x)
#define ts_always_assert() ts_assert(0)
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

#define ts_unused(x) (x)=(x);

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
    template < class TClassType > class unsafe_multi_threaded_access_detector
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
        bool enter(TClassType &storage)
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
        bool exit(TClassType &storage)
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

    class base_scoped_param
    {

    };

    /// <summary>
    /// Class scoped_enter_exit.
    /// </summary>
    /// <seealso cref="T" />
    template < typename TClassType, typename TParam = base_scoped_param > class scoped_enter_exit
    {
      public:
          /// <summary>
          /// Initializes a new instance of the <see cref="scoped_enter_exit"/> class.
          /// </summary>
          /// <param name="_param">The parameter.</param>
          scoped_enter_exit(TParam &_param)
            : param(_param)
        {
              class_type.enter(param);
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="scoped_enter_exit"/> class.
        /// </summary>
        ~scoped_enter_exit() { class_type.exit(param); }

      private:
          /// <summary>
          /// The parameter
          /// </summary>
          TParam &param;
          TClassType class_type;
    };

    template < typename TClassType > class scoped_enter_exit<TClassType, base_scoped_param>
    {
    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="scoped_enter_exit"/> class.
        /// </summary>
        scoped_enter_exit()
        {
            class_type.enter();
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="scoped_enter_exit"/> class.
        /// </summary>
        ~scoped_enter_exit() { class_type.exit(); }

    private:
        TClassType class_type;
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

    template<class TInterface, class TKey = TInterface>
    TInterface* get()
    {
        static TInterface* system = nullptr;
        if (!system)
        {
            system = TInterface::instance<TKey>();
        }
        return system;
    }

    template<class TInterface, class TKey>
    TInterface* create()
    {
        return TInterface::allocate<TKey>();
    }

    template<class TInterface>
    void destroy(TInterface* _interface)
    {
        TInterface::deallocate(_interface);
    }

    template<typename T>
    class attribute
    {
    protected:
        T val;
    public:
        operator T() { return val; }
        T &operator=(const T &_other_val) { val = _other_val; return val; }
    private:
        T *operator&() { return &val; }
    };

    template<typename T, typename TGetFunc, typename TSetFunc>
    class attribute2
    {
    protected:
        T val;
    public:
        operator T() { return TGetFunc(*this); }
        T &operator=(const T &_other_val) { TSetFunc(*this); return val; }
    private:
        T *operator&() { return &val; }
    };
};