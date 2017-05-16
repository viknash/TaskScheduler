// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="allocator.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

/// <summary>
/// Class stl_allocator.
/// </summary>
/// <seealso cref="TMemInterface" />
namespace task_scheduler {
    template < class T, class TMemInterface > class stl_allocator : public TMemInterface
    {
    public:
        //    typedefs
        typedef T value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        //    convert an allocator<T> to allocator<U>

        /// <summary>
        /// Struct rebind
        /// </summary>
        template < typename U, class TMemInterface > struct rebind
        {
            typedef stl_allocator< U, TMemInterface > other;
        };

    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="stl_allocator"/> class.
        /// </summary>
        inline stl_allocator() {}
        /// <summary>
        /// Finalizes an instance of the <see cref="stl_allocator"/> class.
        /// </summary>
        inline ~stl_allocator() {}
        /// <summary>
        /// Initializes a new instance of the <see cref="stl_allocator"/> class.
        /// </summary>
        /// <param name="">The .</param>
        inline stl_allocator(stl_allocator const &) {}
        /// <summary>
        /// Initializes a new instance of the <see cref="stl_allocator"/> class.
        /// </summary>
        /// <param name="">The .</param>
        template < typename U > inline stl_allocator(stl_allocator< U, TMemInterface > const &) {}

        /// <summary>
        /// Addresses the specified r.
        /// </summary>
        /// <param name="r">The r.</param>
        /// <returns>pointer.</returns>
        inline pointer address(reference r) { return &r; }
        /// <summary>
        /// Addresses the specified r.
        /// </summary>
        /// <param name="r">The r.</param>
        /// <returns>const_pointer.</returns>
        inline const_pointer address(const_reference r) { return &r; }

        /// <summary>
        /// Allocates the specified count.
        /// </summary>
        /// <param name="_cnt">The count.</param>
        /// <param name="">The .</param>
        /// <returns>pointer.</returns>
        inline pointer allocate(size_type _cnt, typename std::allocator< void >::const_pointer = 0)
        {
            pointer new_memory = reinterpret_cast<pointer>(operator new(_cnt * sizeof(T)));
            return new_memory;
        }

        /// <summary>
        /// Deallocates the specified p.
        /// </summary>
        /// <param name="_p">The p.</param>
        /// <param name="_n">The n.</param>
        inline void deallocate(pointer _p, size_type _n) { operator delete(_p, _n * sizeof(T)); }

        /// <summary>
        /// Maximums the size.
        /// </summary>
        /// <returns>size_type.</returns>
        inline size_type max_size() const { return std::numeric_limits< size_type >::max() / sizeof(T); }

        /// <summary>
        /// Operator==s the specified .
        /// </summary>
        /// <param name="">The .</param>
        /// <returns>bool.</returns>
        inline bool operator==(stl_allocator const &) const { return true; }

        /// <summary>
        /// Operator!=s the specified a.
        /// </summary>
        /// <param name="_a">a.</param>
        /// <returns>bool.</returns>
        inline bool operator!=(stl_allocator const &_a) { return !operator==(_a); }
    };
}