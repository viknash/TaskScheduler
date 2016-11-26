#pragma once

#if defined(_DEBUG)
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif

inline uint64_t CreateMask64()
{
    return 0;
}

template <typename T, typename... Args>
uint64_t CreateMask64(T first, Args... args)
{
    return CreateMask64(args...) | 1ull << first;
}
