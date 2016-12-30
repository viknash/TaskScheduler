#pragma once

#include <cassert>
#include <memory>

#define ALIGNMENT 16

#pragma pack(ALIGNMENT)
#define class_alignment alignas(ALIGNMENT)

namespace task_scheduler {

    template <class T, class TMemInterface>
    class stl_allocator : public TMemInterface {
    public:
        //    typedefs
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        //    convert an allocator<T> to allocator<U>

        template <typename U, class TMemInterface>
        struct rebind {
            typedef stl_allocator<U, TMemInterface> other;
        };

    public:
        inline stl_allocator() {}
        inline ~stl_allocator() {}
        inline stl_allocator(stl_allocator const&) {}
        template <typename U>
        inline stl_allocator(stl_allocator<U, TMemInterface> const&) {}

        inline pointer address(reference r) { return &r; }
        inline const_pointer address(const_reference r) { return &r; }

        inline pointer allocate(size_type _cnt,
            typename std::allocator<void>::const_pointer = 0)
        {
            pointer new_memory = reinterpret_cast<pointer>(operator new(_cnt * sizeof(T)));
            return new_memory;
        }

        inline void deallocate(pointer _p, size_type _n)
        {
            operator delete(_p, _n * sizeof(T));
        }

        inline size_type max_size() const
        {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        inline bool operator==(stl_allocator const&) const { return true; }

        inline bool operator!=(stl_allocator const& _a) { return !operator==(_a); }
    };

    class default_mem_interface {

        struct metadata_type {
            size_t space;
        };

    public:

        inline void* operator new(size_t _size) { return operator new(_size, ALIGNMENT); };
        inline void* operator new(size_t _size, size_t _alignment);
        inline void* operator new[](size_t _size) { return operator new(_size, ALIGNMENT); };
        inline void* operator new[](size_t _size, size_t _alignment) { return operator new(_size, _alignment); }
        inline void operator delete(void* _ptr, size_t _size);
        inline void operator delete[](void* _ptr, size_t _size) { operator delete(_ptr, _size); }
    };

    static_assert(sizeof(default_mem_interface) == 1, "Not an empty base class");

    inline void* default_mem_interface::operator new(size_t _size, size_t _alignment)
    {
        metadata_type metadata = { 0 };
        metadata.space = _size + sizeof(metadata_type) + _alignment;
        void* raw_pointer = malloc(metadata.space);
        assert(raw_pointer);
        void* aligned_pointer = std::align(_alignment, _size + sizeof(metadata_type), raw_pointer, metadata.space);
        assert(aligned_pointer);
        *(metadata_type*)((char*)aligned_pointer + _size) = metadata;
        return aligned_pointer;
    }

    inline void default_mem_interface::operator delete(void* _ptr, size_t _size)
    {
        size_t alignment = ALIGNMENT;
        void* aligned_pointer = _ptr;
        metadata_type* metadata = (metadata_type*)((char*)aligned_pointer + _size);
        void* raw_pointer = (void*)((char*)aligned_pointer - (_size + sizeof(metadata_type) + alignment - metadata->space));
        free(raw_pointer);
    }

#define task_scheduler_default_mem_interface_catch_all_allocations() \
    default_mem_interface gDefaultMemInterface; \
    void* operator new(size_t n){return gDefaultMemInterface.operator new(n);} \
    void operator delete(void* p, size_t n) throw() {gDefaultMemInterface.operator delete(p, n);} \
    void* operator new[](size_t n){return gDefaultMemInterface.operator new[](n);} \
    void operator delete[](void* p, size_t n) throw() {gDefaultMemInterface.operator delete[](p, n);}

};