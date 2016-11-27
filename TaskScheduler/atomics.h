#pragma once

#include <cstdint>

#if defined(_MSC_VER)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif //!defined(NOMINMAX)
#include <windows.h>
#endif

namespace task_scheduler {

    namespace atomics {
        inline int64_t increment(volatile int64_t& _data)
        {
            return _InterlockedIncrement64(&_data);
        }

        inline int64_t decrement(volatile int64_t& _data)
        {
            return _InterlockedDecrement64(&_data);
        }

        inline int32_t increment(volatile int32_t& _data)
        {
            return _InterlockedIncrement(reinterpret_cast<volatile long*>(&_data));
        }

        inline int32_t decrement(volatile int32_t& _data)
        {
            return _InterlockedDecrement(reinterpret_cast<volatile long*>(&_data));
        }

        inline int32_t compare_exchange_weak(volatile int32_t& _data, int32_t _comperand, int32_t _value)
        {
            return _InterlockedCompareExchange(reinterpret_cast<volatile long*>(&_data), static_cast<long>(_value), static_cast<long>(_comperand));
        }

        inline int64_t compare_exchange_weak(volatile int64_t& _data, int64_t _comperand, int64_t _value)
        {
            return _InterlockedCompareExchange64(&_data, _value, _comperand);
        }

        template <class T>
        inline T* compare_exchange_weak(T* volatile& _data, T* _comperand, T* _value)
        {
            return reinterpret_cast<T*>(_InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(&_data), reinterpret_cast<void*>(_value), reinterpret_cast<void*>(_comperand)));
        }

        inline bool compare_exchange_weak_128(volatile int64_t _data[], int64_t _comperand[], int64_t _value_hi, int64_t _value_lo)
        {
            return _InterlockedCompareExchange128(_data, _value_hi, _value_lo, _comperand) == 1;
        }

        typedef int64_t type;
    };

};
