// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="memory.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <cassert>
#include <memory>

#define ALIGNMENT 16

#pragma pack(ALIGNMENT)
#define class_alignment alignas(ALIGNMENT)

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// Class stl_allocator.
    /// </summary>
    /// <seealso cref="TMemInterface" />
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
            pointer new_memory = reinterpret_cast< pointer >(operator new(_cnt * sizeof(T)));
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

    /// <summary>
    /// Class default_mem_interface.
    /// </summary>
    class default_mem_interface
    {

        /// <summary>
        /// Struct metadata_type
        /// </summary>
        struct metadata_type
        {
            /// <summary>
            /// The space
            /// </summary>
            size_t space;
        };

      public:
          /// <summary>
          /// Implements the operator new operator.
          /// </summary>
          /// <param name="_size">The size.</param>
          /// <returns>The result of the operator.</returns>
          inline void *operator new(size_t _size) { return operator new(_size, ALIGNMENT); };

        /// <summary>
        /// Implements the operator new operator.
        /// </summary>
        /// <param name="_size">The size.</param>
        /// <param name="_alignment">The alignment.</param>
        /// <returns>The result of the operator.</returns>
        inline void *operator new(size_t _size, size_t _alignment);
        /// <summary>
        /// Implements the operator new[] operator.
        /// </summary>
        /// <param name="_size">The size.</param>
        /// <returns>The result of the operator.</returns>
        inline void *operator new[](size_t _size) { return operator new(_size, ALIGNMENT); };
        /// <summary>
        /// Implements the operator new[] operator.
        /// </summary>
        /// <param name="_size">The size.</param>
        /// <param name="_alignment">The alignment.</param>
        /// <returns>The result of the operator.</returns>
        inline void *operator new[](size_t _size, size_t _alignment) { return operator new(_size, _alignment); }
            /// <summary>
            /// Implements the operator delete operator.
            /// </summary>
            /// <param name="_ptr">The PTR.</param>
            /// <param name="_size">The size.</param>
            /// <returns>The result of the operator.</returns>
        inline void operator delete(void *_ptr, size_t _size);
        /// <summary>
        /// Implements the operator delete[] operator.
        /// </summary>
        /// <param name="_ptr">The PTR.</param>
        /// <param name="_size">The size.</param>
        /// <returns>The result of the operator.</returns>
        inline void operator delete[](void *_ptr, size_t _size) { operator delete(_ptr, _size); }
    };

    static_assert(sizeof(default_mem_interface) == 1, "Not an empty base class");


    inline void *default_mem_interface::operator new(size_t _size, size_t _alignment)
    {
        metadata_type metadata = {0};
        metadata.space = _size + sizeof(metadata_type) + _alignment;
        void *raw_pointer = malloc(metadata.space);
        assert(raw_pointer);
        void *aligned_pointer = std::align(_alignment, _size + sizeof(metadata_type), raw_pointer, metadata.space);
        assert(aligned_pointer);
        *(metadata_type *)((char *)aligned_pointer + _size) = metadata;
        return aligned_pointer;
    }

    inline void default_mem_interface::operator delete(void *_ptr, size_t _size)
    {
        size_t alignment = ALIGNMENT;
        void *aligned_pointer = _ptr;
        metadata_type *metadata = (metadata_type *)((char *)aligned_pointer + _size);
        void *raw_pointer =
            (void *)((char *)aligned_pointer - (_size + sizeof(metadata_type) + alignment - metadata->space));
        free(raw_pointer);
    }

#define task_scheduler_default_mem_interface_catch_all_allocations()                                                   \
    default_mem_interface gDefaultMemInterface;                                                                        \
    void *operator new(size_t n) { return gDefaultMemInterface.operator new(n); }                                      \
    void operator delete(void *p, size_t n) throw() { gDefaultMemInterface.operator delete(p, n); }                    \
    void *operator new[](size_t n) { return gDefaultMemInterface.operator new[](n); }                                  \
    void operator delete[](void *p, size_t n) throw() { gDefaultMemInterface.operator delete[](p, n); }
};