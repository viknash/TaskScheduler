#pragma once

typedef chrono::time_point<chrono::high_resolution_clock> ProfileTimePoint;
typedef chrono::high_resolution_clock ProfileClock;
typedef chrono::microseconds ProfileTime;

struct ProfileTimer {
    ProfileTimer(chrono::microseconds& _elapsedTime)
        : start(ProfileClock::now())
        , elapsedTime(_elapsedTime)
    {
    }

    ~ProfileTimer()
    {
        elapsedTime += chrono::duration_cast<chrono::microseconds>(
            ProfileClock::now() - start);
    }

    ProfileTimePoint start;
    ProfileTime& elapsedTime;
};

template <typename ReturnType, typename ClassType, typename MemFunc,
    typename... Args>
    ReturnType Instrument(ProfileTime& profileTime, ClassType* classType,
        MemFunc func, Args... params)
{
    ProfileTimer profile(profileTime);
    return (classType->*func)(std::forward<Args>(params)...);
}
