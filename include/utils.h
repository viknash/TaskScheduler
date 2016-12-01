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

    template<class T>
    class unsafe_multi_threaded_access_detector
    {

    public:
        inline unsafe_multi_threaded_access_detector() :
            previous_thread_id(0)
        {
        }

        inline void enter(T& storage)
        {
            int64_t new_thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
            previous_thread_id = storage.exchange(new_thread_id);
            assert(previous_thread_id == 0 || previous_thread_id == new_thread_id);
        }

        inline void exit(T& storage)
        {
            int64_t stored_thread_id = storage.exchange(previous_thread_id);
            int64_t current_thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
            assert(stored_thread_id == current_thread_id || stored_thread_id == 0);
        }

    private:
        std::atomic_int64_t previous_thread_id;
    };

    template<typename T, typename TParam>
    class scoped_enter_exit : public T
    {
        scoped_enter_exit(TParam& _param) :
            param(_param)
        {
            enter(param);
        }

        ~scoped_enter_exit()
        {
            exit(param);
        }

        T param;
    };

    typedef scoped_enter_exit<unsafe_multi_threaded_access_detector<std::atomic_int64_t>, std::atomic_int64_t> thread_unsafe_access_guard;
    typedef std::atomic_int64_t thread_unsafe_access_storage;
};