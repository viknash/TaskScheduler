#pragma once

#include <atomic>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

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

#define ts_join_string(arg0, arg1) ts_do_join(arg0, arg1)
#define ts_do_join(arg0, arg1) arg0##arg1

#define ts_unique_variable(basename) ts_join_string(basename, __COUNTER__)

namespace task_scheduler
{

    inline thread_mask_int_t create_mask_64() { return 0; }

    template < typename T, typename... Args > thread_mask_int_t create_mask_64(T first, Args... args)
    {
        return create_mask_64(args...) | 1ull << first;
    }

    template < class T > class unsafe_multi_threaded_access_detector
    {

      public:
        unsafe_multi_threaded_access_detector()
            : previous_thread_id(0)
        {
        }

        bool enter(T &storage)
        {
            int64_t new_thread_id = std::hash< std::thread::id >()(std::this_thread::get_id());
            previous_thread_id = storage.last_thread_id.exchange(new_thread_id);
            bool success = previous_thread_id == 0 || previous_thread_id == new_thread_id;
            assert(success);
            return success;
        }

        bool exit(T &storage)
        {
            int64_t stored_thread_id = storage.last_thread_id.exchange(previous_thread_id);
            int64_t current_thread_id = std::hash< std::thread::id >()(std::this_thread::get_id());
            bool success = stored_thread_id == current_thread_id || stored_thread_id == 0;
            assert(success);
            return success;
        }

      private:
        std::atomic_int64_t previous_thread_id;
    };

    template < typename T, typename TParam > class scoped_enter_exit : public T
    {
      public:
        scoped_enter_exit(TParam &_param)
            : param(_param)
        {
            this->enter(param);
        }

        ~scoped_enter_exit() { this->exit(param); }

      private:
        TParam &param;
    };

    struct thread_unsafe_access_storage
    {
        thread_unsafe_access_storage()
            : last_thread_id(0)
        {
        }
        std::atomic_int64_t last_thread_id;
    };

    typedef scoped_enter_exit< unsafe_multi_threaded_access_detector< thread_unsafe_access_storage >,
                               thread_unsafe_access_storage >
        thread_unsafe_access_guard;
};