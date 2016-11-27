#pragma once

#include <thread>

namespace task_scheduler {

    typedef std::chrono::time_point<std::chrono::high_resolution_clock> profile_time_point;
    typedef std::chrono::high_resolution_clock profile_clock;
    typedef std::chrono::microseconds profile_time;

    struct profile_timer {
        profile_timer(std::chrono::microseconds& _elapsedTime)
            : start(profile_clock::now())
            , elapsedTime(_elapsedTime)
        {
        }

        ~profile_timer()
        {
            elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(
                profile_clock::now() - start);
        }

        profile_time_point start;
        profile_time& elapsedTime;
    };

    template <typename TReturnType, typename TClassType, typename TMemFunc,
        typename... TArgs>
        TReturnType instrument(profile_time& _profileTime, TClassType* _classType,
            TMemFunc _func, TArgs... _params)
    {
        profile_timer profile(_profileTime);
        return (_classType->*_func)(forward<TArgs>(_params)...);
    }

};