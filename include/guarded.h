// ***********************************************************************
// <copyright file="guarded.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

namespace task_scheduler {

    template < typename T, class TDataStructure, class TMemInterface > class guarded : private TDataStructure
    {
        typedef TDataStructure super;

    public:
        guarded(size_t _fixed_size);
        T &operator[](size_t _index);
        T &at(size_t _index);
        T &front();
        T &back();
        void push_back(const T &_new_item);
        void clear();
        typename TDataStructure::size_type size() const _NOEXCEPT;

        bool is_locked();

        template < typename T, class TDataType, class TMemInterface > friend class lock_free_batch_dispatcher;

    private:
        std::atomic_bool read_locked;

        void lock(T *&_locked_data);
        void unlock(T *&_unlocked_data);
        void _Reallocate(typename TDataStructure::size_type _Count);
    };

    template < typename T, class TDataStructure, class TMemInterface >
    guarded< T, TDataStructure, TMemInterface >::guarded(size_t _fixed_size)
        : TDataStructure(_fixed_size)
        , read_locked(false)
    {

    }

    template < typename T, class TDataStructure, class TMemInterface >
    void guarded< T, TDataStructure, TMemInterface >::lock(T *&_locked_data)
    {
        bool previous_value = read_locked.exchange(true);
        ts_assert(!previous_value); // Array has already been locked before
        _locked_data = super::data();
    }

    template < typename T, class TDataStructure, class TMemInterface >
    void guarded< T, TDataStructure, TMemInterface >::unlock(T *&_unlocked_data)
    {
        //Array could have been resized, reserve a larger amount of elements
        ts_assert(super::data() == _unlocked_data);
        _unlocked_data = nullptr;
        bool previous_value = read_locked.exchange(false);
        ts_assert(previous_value); // Array not been locked before
    }

    template < typename T, class TDataStructure, class TMemInterface >
    bool guarded< T, TDataStructure, TMemInterface >::is_locked()
    {
        return read_locked;
    }

    template < typename T, class TDataStructure, class TMemInterface >
    void guarded< T, TDataStructure, TMemInterface >::push_back(const T &_new_item)
    {
        ts_assert(!is_locked()); // Array has been locked for reading
        if (!is_locked())
        {
            super::push_back(_new_item);
        }
    }

    template < typename T, class TDataStructure, class TMemInterface >
    void guarded< T, TDataStructure, TMemInterface >::clear()
    {
        ts_assert(!is_locked()); // Array has been locked for reading
        if (!is_locked())
        {
            super::clear();
        }
    }

    template < typename T, class TDataStructure, class TMemInterface >
    T &guarded< T, TDataStructure, TMemInterface >::operator[](size_t _index)
    {
        return at(_index);
    }

    template < typename T, class TDataStructure, class TMemInterface >
    T &guarded< T, TDataStructure, TMemInterface >::at(size_t _index)
    {
        ts_assert(_index < super::size()); // Index out of bounds
        return super::data() + _index;
    }

    template < typename T, class TDataStructure, class TMemInterface >
    T &guarded< T, TDataStructure, TMemInterface >::front()
    {
        return at(0);
    }

    template < typename T, class TDataStructure, class TMemInterface >
    T &guarded< T, TDataStructure, TMemInterface >::back()
    {
        ts_assert(super::size() > 0);
        return at(super::size() - 1);
    }

    template < typename T, class TDataStructure, class TMemInterface >
    void guarded< T, TDataStructure, TMemInterface >::_Reallocate(typename TDataStructure::size_type _Count)
    {
        ts_assert(!is_locked()); //Data structure is being resized, the lock is no longer valid
                                 //Increase the initial size of the data structure
        super::_Reallocate(_Count);
    }

    template < typename T, class TDataStructure, class TMemInterface >
    typename TDataStructure::size_type guarded< T, TDataStructure, TMemInterface >::size() const _NOEXCEPT
    {
        return super::size();
    }

    template < typename T, class TMemInterface >
    using guarded_vector = guarded< T, std::vector< T, stl_allocator< T, TMemInterface > >, TMemInterface >;
}