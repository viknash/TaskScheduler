#pragma once

#include <cstdint>

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

#if 0
    class multi_threaded_detector
    {

    public:
        inline multi_threaded_detector()
        {
            previous_thread_id = 0;
        }

        inline void enter()
        {
            int64_t current_thread_id = std::this_thread::get_id();
            previous_thread_id = G4::Atomic::Exchange(detector.GetCurrentThreadId(), currentThread);
            bool valid = m_PreviousThreadId == currentThread || m_PreviousThreadId == 0;
            assert(valid);
        }

        inline void Exit(MultiThreadDetector& detector)
        {
            int64_t previousThreadId = exchange(detector.GetCurrentThreadId(), m_PreviousThreadId);
            int64_t currentThread = std::this_thread::get_id();
            bool valid = previousThreadId == currentThread || previousThreadId == 0;
            assert!(valid);
        }

    private:

        std::atomic_int64_t previous_thread_id;
    };
#endif

};