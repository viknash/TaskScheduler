#pragma once

#include <cstdint>
#include <thread>
#include <atomic>

#if defined(_DEBUG)
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif

#define unique_variable(basename) basename##__LINE__

namespace task_scheduler {

    inline uint64_t CreateMask64()
    {
        return 0;
    }

    template <typename T, typename... Args>
    uint64_t CreateMask64(T first, Args... args)
    {
        return CreateMask64(args...) | 1ull << first;
    }

    class unsafe_multi_threaded_access_detector
    {

    public:
        inline unsafe_multi_threaded_access_detector()
        {
            currently_accessing_thread_id = 0;
        }

        inline void enter()
        {
            int64_t current_thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
            int64_t previous_thread_id = currently_accessing_thread_id.exchange(current_thread_id);
            assert(previous_thread_id == 0); previous_thread_id;
        }

        inline void exit()
        {
            int64_t previous_thread_id = currently_accessing_thread_id.exchange(0);
            int64_t current_thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
            assert(previous_thread_id == current_thread_id); current_thread_id; previous_thread_id;
        }

    private:
        std::atomic_int64_t currently_accessing_thread_id;
    };

    template<typename T>
    class scoped_enter_exit
    {
        scoped_enter_exit(T& _item) :
            item(_item)
        {
            item.enter();
        }

        ~scoped_enter_exit()
        {
            item.exit();
        }

        T item;
    };

    typedef scoped_enter_exit<unsafe_multi_threaded_access_detector> thread_unsafe_access_guard;
};