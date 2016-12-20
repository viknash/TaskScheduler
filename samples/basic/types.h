#pragma once

#include <cstdint>

namespace task_scheduler {

    template <typename ValueType, uint32_t MinValue, uint32_t MaxValue, bool MinInclusive = false, bool MaxInclusive = true>
    class constrained {
        typedef ValueType value_type;

        operator const value_type & () const { return value(); }

        void operator=(const ValueType& _value)
        {
            assert((MinInclusive ? _value >= (ValueType)MinValue : _value > (ValueType)MinValue) && (maxInclusive ? _value <= (ValueType)MaxValue : _value < (ValueType)MaxValue));
            value = _value;
        }

        operator const ValueType()
        {
            return value;
        }

    private:
        ValueType value;
    };

    typedef constrained<float, 0, 100> percentage_t;
}