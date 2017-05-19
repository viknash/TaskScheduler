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


#include <memory>
#include <atomic>

#include "utils.h"
#include "profile.h"
#include "alignment.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{


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
        void *operator new(size_t _size, size_t _alignment);
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
        void operator delete(void *_ptr, size_t _size);
        /// <summary>
        /// Implements the operator delete[] operator.
        /// </summary>
        /// <param name="_ptr">The PTR.</param>
        /// <param name="_size">The size.</param>
        /// <returns>The result of the operator.</returns>
        inline void operator delete[](void *_ptr, size_t _size) { operator delete(_ptr, _size); }

    };

     void *default_mem_interface::operator new(size_t _size, size_t _alignment)
    {
        metadata_type metadata = { 0 };
        metadata.space = _size + sizeof(metadata_type) + _alignment;
        profile::memory* profile = get<profile::memory, default_mem_interface>();
        profile->allocate_begin(metadata.space, false);
        void *raw_pointer = malloc(metadata.space);
        profile->allocate_end(&raw_pointer, metadata.space, false);
        ts_assert(raw_pointer);
        void *aligned_pointer = std::align(_alignment, _size + sizeof(metadata_type), raw_pointer, metadata.space);
        ts_assert(aligned_pointer);
        *(metadata_type *)((char *)aligned_pointer + _size) = metadata;
        return aligned_pointer;
    }

    void default_mem_interface::operator delete(void *_ptr, size_t _size)
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