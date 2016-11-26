#pragma once

#define ALIGNMENT 16

#pragma pack(ALIGNMENT)
#define class_alignment alignas(ALIGNMENT)

template <class T, class MemInterface>
class Allocator : public MemInterface {
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

    template <typename U, class MemInterface>
    struct rebind {
        typedef Allocator<U, MemInterface> other;
    };

public:
    inline Allocator() {}
    inline ~Allocator() {}
    inline Allocator(Allocator const&) {}
    template <typename U>
    inline Allocator(Allocator<U, MemInterface> const&) {}

    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    inline pointer allocate(size_type cnt,
        typename allocator<void>::const_pointer = 0)
    {
        // cout << "Trying to allocate " << cnt << " objects in memory" << endl;
        pointer new_memory = reinterpret_cast<pointer>(operator new(cnt * sizeof(T)));
        // cout << "Allocated " << cnt << " objects in memory at location:" <<
        // new_memory << endl;
        return new_memory;
    }

    inline void deallocate(pointer p, size_type n)
    {
        operator delete(p, n * sizeof(T));
        // cout << "Deleted " << n << " objects from memory" << endl;
    }

    inline size_type max_size() const
    {
        return numeric_limits<size_type>::max() / sizeof(T);
    }

    inline bool operator==(Allocator const&) const { return true; }

    inline bool operator!=(Allocator const& a) { return !operator==(a); }
};

class DefaultMemInterface {
    struct Metadata {
        size_t space;
    };

public:
    // Use global new/delete
    void* DefaultMemInterface::operator new(size_t size)
    {
        // cout << "custom new for size " << size << '\n';
        size_t alignment = ALIGNMENT;
        Metadata metadata = { 0 };
        metadata.space = size + sizeof(Metadata) + alignment;
        void* raw_pointer = malloc(metadata.space);
        assert(raw_pointer);
        void* aligned_pointer = align(alignment, size + sizeof(Metadata), raw_pointer, metadata.space);
        assert(aligned_pointer);
        *(Metadata*)((char*)aligned_pointer + size) = metadata;
        return aligned_pointer;
    }

    void* DefaultMemInterface::operator new[](size_t counter)
    {
        // cout << "custom new for size " << counter << '\n';
        return operator new(counter);
    }

    void operator delete(void* ptr, size_t size)
    {
        // cout << "custom delete for size " << size << '\n';
        size_t alignment = ALIGNMENT;
        void* aligned_pointer = ptr;
        Metadata* metadata = (Metadata*)((char*)aligned_pointer + size);
        void* raw_pointer = (void*)((char*)aligned_pointer - (size + sizeof(Metadata) + alignment - metadata->space));
        free(raw_pointer);
    }

    void operator delete[](void* ptr, size_t counter)
    {
        // cout << "custom delete for size " << counter << '\n';
        operator delete(ptr, counter);
    }
};

static_assert(sizeof(DefaultMemInterface) == 1, "Not an empty base class");