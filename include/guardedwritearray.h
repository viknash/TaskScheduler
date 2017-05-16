// ***********************************************************************
// <copyright file="guardedwritearray.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

namespace task_scheduler {

    template < typename T, class TMemInterface >
    class guarded_write_array : public TMemInterface
    {

    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="guarded_write_array"/> class.
        /// </summary>
        /// <param name="_reserved_size">Size of the reserved.</param>
        /// <param name="_optimize_for_cache_line_size">Size of the optimize for cache line.</param>
        guarded_write_array(size_t _reserverd_size, bool _optimize_for_cache_line_size);
        /// <summary>
        /// Initializes a new instance of the <see cref="guarded_write_array"/> class.
        /// </summary>
        /// <param name="_existing_array">The existing array.</param>
        /// <param name="_existing_array_size">Size of the existing array.</param>
        guarded_write_array(T *_existing_array, size_t _existing_array_size);
        /// <summary>
        /// Finalizes an instance of the <see cref="guarded_write_array"/> class.
        /// </summary>
        ~guarded_write_array();        /// <summary>
                                       /// Sizes this instance.
                                       /// </summary>
                                       /// <returns>size_t.</returns>
        size_t size() { return array_size; }
        /// <summary>
        /// Reserveds this instance.
        /// </summary>
        /// <returns>size_t.</returns>
        size_t reserved() { return array_flags.reserved_size; }

        /// <summary>
        /// Operator&s this instance.
        /// </summary>
        /// <returns>T *.</returns>
        T *operator&();
        /// <summary>
        /// Pushes the back.
        /// </summary>
        /// <param name="_new_item">The new item.</param>
        void push_back(const T &_new_item);
        /// <summary>
        /// Clears this instance.
        /// </summary>
        void clear();
        /// <summary>
        /// Operator[]s the specified index.
        /// </summary>
        /// <param name="_index">The index.</param>
        /// <returns>T &.</returns>
        T& operator[](size_t _index);

        template < typename T, class TMemInterface > friend class guarded_write_array_batch_dispenser;

        union flags {
            size_t reserved_size : 62;
            size_t read_locked : 1;
            size_t data_owner : 1;
        };

    private:
        /// <summary>
        /// Locks this instance.
        /// </summary>
        void lock();
        /// <summary>
        /// Unlocks this instance.
        /// </summary>
        void unlock();
        /// <summary>
        /// The array flags
        /// </summary>
        /// <returns>bool.</returns>
        /// /
        bool is_locked();

        /// <summary>
        /// The data
        /// </summary>
        T *data;
        /// <summary>
        /// The array size
        /// </summary>
        std::atomic< size_t > array_size;
        flags array_flags;
    };

    template < typename T, class TMemInterface >
    inline guarded_write_array< T, TMemInterface >::guarded_write_array(size_t _reserved_size,
        bool _optimize_for_cache_line_size)
        : array_size(0)
        , flags(0)
    {
        array_flags.reserved_size = ~0;
        assert(_reserved_size < array_flags.reserved_size); // Requested size is too large
        array_flags.reserved_size = _reserved_size;
        array_flags.data_owner = 1;
        uint32_t cache_line_size = _optimize_for_cache_line_size ? get_cache_line_size() : 1;
        data = new (cache_line_size) T[array_size];
    }

    template < typename T, class TMemInterface >
    inline guarded_write_array< T, TMemInterface >::guarded_write_array(T *_existing_array, size_t _existing_array_size)
        : data(_existing_array)
        , array_size(_existing_array_size)
    {
        array_flags.reserved_size = _existing_array_size;
        array_flags.data_owner = 0;
    }

    template < typename T, class TMemInterface > inline guarded_write_array< T, TMemInterface >::~guarded_write_array()
    {
        if (array_flags.data_owner)
        {
            delete[] data;
        }
        ts_debug_only(data = nullptr;);
        ts_debug_only(array_flags = 0;);
        ts_debug_only(array_size = 0;);
    }

    template < typename T, class TMemInterface >
    inline T &guarded_write_array< T, TMemInterface >::operator[](size_t _index)
    {
        assert(_index < array_size); // Index out of bounds
        return data + _index;
    }


    template < typename T, class TMemInterface >
    inline void guarded_write_array< T, TMemInterface >::push_back(const T &_new_item)
    {
        ++array_size;
        assert(array_size <= array_flags.reserved_size); // Exceeded size of array
        assert(!is_locked());                            // Array has been locked for reading
        *(data + array_size - 1) = _new_item;
    }


    template < typename T, class TMemInterface > inline void guarded_write_array< T, TMemInterface >::clear()
    {
        assert(!is_locked()); // Array has been locked for reading
        array_size = 0;
    }


    template < typename T, class TMemInterface > inline T *guarded_write_array< T, TMemInterface >::operator&()
    {
        assert(!is_locked()); // Array has been locked for reading
        return data;
    }


    template < typename T, class TMemInterface > inline void guarded_write_array< T, TMemInterface >::lock()
    {
        assert(!array_flags.read_locked); // Array has already been locked before
        array_flags.read_locked = 1;
    }


    template < typename T, class TMemInterface > inline void guarded_write_array< T, TMemInterface >::unlock()
    {
        assert(array_flags.read_locked); // Array has already been unlocked before
        array_flags.read_locked = 0;
    }


    template < typename T, class TMemInterface > inline bool guarded_write_array< T, TMemInterface >::is_locked()
    {
        return array_flags.read_locked;
    }
}