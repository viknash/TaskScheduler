#pragma once

#include <cstdint>

namespace task_scheduler
{

    template < typename ValueType, uint32_t MinValue, uint32_t MaxValue, bool MinInclusive = false,
               bool MaxInclusive = true >
    class constrained
    {
        typedef ValueType value_type;

        operator const value_type &() const { return value(); }

        void operator=(const ValueType &_value)
        {
            assert((MinInclusive ? _value >= (ValueType)MinValue : _value > (ValueType)MinValue) &&
                   (maxInclusive ? _value <= (ValueType)MaxValue : _value < (ValueType)MaxValue));
            value = _value;
        }

        operator const ValueType() { return value; }

      private:
        ValueType value;
    };

    typedef constrained< float, 0, 100 > percentage_t;

    template < class TMemInterface > class base_thread_pool;

    typedef uint8_t thread_num_t;
    typedef uint64_t thread_mask_int_t;

    template < typename ValueType, class TMemInterface > class base_thread_index
    {
        typedef base_thread_pool< TMemInterface > thread_pool;

      public:
        base_thread_index(thread_pool *_pool, ValueType _value)
            : value(_value)
            , pool(_pool)
        {
        }

        base_thread_index &operator++()
        {
            *this += 1;
            return *this;
        }

        base_thread_index &operator--()
        {
            *this -= 1;
            return *this;
        }

        base_thread_index &operator+=(const base_thread_index &rhs)
        {
            value = (value + rhs) % pool->num_threads;
            return *this;
        }

        base_thread_index &operator+=(int32_t rhs)
        {
            value = (value + rhs) % pool->num_threads;
            return *this;
        }

        friend base_thread_index operator+(base_thread_index lhs, const base_thread_index &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        base_thread_index &operator-=(const base_thread_index &rhs)
        {
            value = (value + pool->num_threads - rhs) % pool->num_threads;
            return *this;
        }

        base_thread_index &operator-=(int32_t rhs)
        {
            value = (value + pool->num_threads - rhs) % pool->num_threads;
            return *this;
        }

        base_thread_index(const base_thread_index &other)
        {
            pool = other.pool;
            value = other.value;
        }

        base_thread_index &operator=(const base_thread_index &other) // copy assignment
        {
            if (this != &other)
            { // self-assignment check expected
                pool = other.pool;
                value = other.value;
            }
            return *this;
        }

        operator const ValueType() { return value; }

        thread_mask_int_t get_mask() { return 1ull << value; }

        bool is_set(thread_mask_int_t _other_mask)
        {
            thread_mask_int_t this_mask = get_mask();
            return ((this_mask & _other_mask) == this_mask);
        }

      private:
        ValueType value;
        thread_pool *pool;
    };

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface >
    operator+(base_thread_index< ValueType, TMemInterface > lhs,
              const base_thread_index< ValueType, TMemInterface > &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface > operator+(base_thread_index< ValueType, TMemInterface > lhs,
                                                                   int32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface >
    operator+(int32_t lhs, const base_thread_index< ValueType, TMemInterface > &rhs)
    {
        return rhs + lhs;
    }

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface >
    operator-(base_thread_index< ValueType, TMemInterface > lhs,
              const base_thread_index< ValueType, TMemInterface > &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface > operator-(base_thread_index< ValueType, TMemInterface > lhs,
                                                                   int32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    template < typename ValueType, class TMemInterface >
    inline base_thread_index< ValueType, TMemInterface >
    operator-(int32_t lhs, const base_thread_index< ValueType, TMemInterface > &rhs)
    {
        return rhs - lhs;
    }

    template < class TMemInterface > using thread_index_t = base_thread_index< thread_num_t, TMemInterface >;
}