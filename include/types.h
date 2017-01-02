// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="types.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <cstdint>

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// Class constrained.
    /// </summary>
    template < typename ValueType, uint32_t MinValue, uint32_t MaxValue, bool MinInclusive = false,
               bool MaxInclusive = true >
    class constrained
    {
        typedef ValueType value_type;

        /// <summary>
        /// Implements the operator const value_type&amp; operator.
        /// </summary>
        /// <returns>The result of the operator.</returns>
        operator const value_type &() const { return value(); }

        /// <summary>
        /// Operator=s the specified value.
        /// </summary>
        /// <param name="_value">The value.</param>
        void operator=(const ValueType &_value)
        {
            assert((MinInclusive ? _value >= (ValueType)MinValue : _value > (ValueType)MinValue) &&
                   (maxInclusive ? _value <= (ValueType)MaxValue : _value < (ValueType)MaxValue));
            value = _value;
        }

        /// <summary>
        /// Implements the operator const ValueType operator.
        /// </summary>
        /// <returns>The result of the operator.</returns>
        operator const ValueType() { return value; }

      private:
          /// <summary>
          /// The value
          /// </summary>
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
          /// <summary>
          /// Initializes a new instance of the <see cref="base_thread_index"/> class.
          /// </summary>
          /// <param name="_pool">The pool.</param>
          /// <param name="_value">The value.</param>
          base_thread_index(thread_pool *_pool, ValueType _value)
            : value(_value)
            , pool(_pool)
        {
        }

          /// <summary>
          /// Operator++s this instance.
          /// </summary>
          /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
          base_thread_index &operator++()
        {
            *this += 1;
            return *this;
        }

          /// <summary>
          /// Operator--s this instance.
          /// </summary>
          /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
          base_thread_index &operator--()
        {
            *this -= 1;
            return *this;
        }

          /// <summary>
          /// Operator+=s the specified RHS.
          /// </summary>
          /// <param name="rhs">The RHS.</param>
          /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
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

        /// <summary>
        /// Operator+s the specified LHS.
        /// </summary>
        /// <param name="lhs">The LHS.</param>
        /// <param name="rhs">The RHS.</param>
        /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt;.</returns>
        friend base_thread_index operator+(base_thread_index lhs, const base_thread_index &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        /// <summary>
        /// Operator-=s the specified RHS.
        /// </summary>
        /// <param name="rhs">The RHS.</param>
        /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
        base_thread_index &operator-=(const base_thread_index &rhs)
        {
            value = (value + pool->num_threads - rhs) % pool->num_threads;
            return *this;
        }

        /// <summary>
        /// Operator-=s the specified RHS.
        /// </summary>
        /// <param name="rhs">The RHS.</param>
        /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
        base_thread_index &operator-=(int32_t rhs)
        {
            value = (value + pool->num_threads - rhs) % pool->num_threads;
            return *this;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="base_thread_index"/> class.
        /// </summary>
        /// <param name="other">The other.</param>
        base_thread_index(const base_thread_index &other)
        {
            pool = other.pool;
            value = other.value;
        }

        /// <summary>
        /// Operator=s the specified other.
        /// </summary>
        /// <param name="other">The other.</param>
        /// <returns>task_scheduler.base_thread_index&lt;ValueType, TMemInterface&gt; &.</returns>
        base_thread_index &operator=(const base_thread_index &other) // copy assignment
        {
            if (this != &other)
            { // self-assignment check expected
                pool = other.pool;
                value = other.value;
            }
            return *this;
        }

        /// <summary>
        /// Implements the operator const ValueType operator.
        /// </summary>
        /// <returns>The result of the operator.</returns>
        operator const ValueType() { return value; }

        /// <summary>
        /// Gets the mask.
        /// </summary>
        /// <returns>thread_mask_int_t.</returns>
        thread_mask_int_t get_mask() { return 1ull << value; }

        /// <summary>
        /// Determines whether the specified other mask is set.
        /// </summary>
        /// <param name="_other_mask">The other mask.</param>
        /// <returns>bool.</returns>
        bool is_set(thread_mask_int_t _other_mask)
        {
            thread_mask_int_t this_mask = get_mask();
            return ((this_mask & _other_mask) == this_mask);
        }

      private:
          /// <summary>
          /// The value
          /// </summary>
          ValueType value;
          /// <summary>
          /// The pool
          /// </summary>
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