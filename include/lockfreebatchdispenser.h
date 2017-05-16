// ***********************************************************************
// <copyright file="lockfreebatchdispenser.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once


namespace task_scheduler {

    /// <summary>
    /// Class lock_free_batch_dispatcher.
    /// </summary>
    /// <seealso cref="TMemInterface" />
    template < typename T, class TDataType, class TMemInterface >
    class lock_free_batch_dispatcher : public TMemInterface
    {
    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="lock_free_batch_dispatcher" /> class.
        /// </summary>
        /// <param name="_data_type">Type of the data.</param>
        lock_free_batch_dispatcher(TDataType &_data_type);
        /// <summary>
        /// Finalizes an instance of the <see cref="lock_free_batch_dispatcher" /> class.
        /// </summary>
        ~lock_free_batch_dispatcher();
        /// <summary>
        /// Gets the next batch.
        /// </summary>
        /// <param name="_requested_batch_size">Size of the requested batch.</param>
        /// <param name="_returned_batch_size">Size of the returned batch.</param>
        /// <returns>T *.</returns>
        T *get_next_batch(size_t _requested_batch_size, size_t &_returned_batch_size);

    private:
        /// <summary>
        /// The data
        /// </summary>
        TDataType &data;
        /// <summary>
        /// The locked data
        /// </summary>
        T *locked_data;
        /// <summary>
        /// The next batch index
        /// </summary>
        std::atomic< size_t > next_batch_index;
    };


    template < typename T, class TDataType, class TMemInterface >
    lock_free_batch_dispatcher< T, TDataType, TMemInterface >::lock_free_batch_dispatcher(
        TDataType &_guarded_data_structure)
        : data(_guarded_data_structure)
        , locked_data(nullptr)
        , next_batch_index(0)
    {
        data.lock(locked_data);
    }


    template < typename T, class TDataType, class TMemInterface >
    lock_free_batch_dispatcher< T, TDataType, TMemInterface >::~lock_free_batch_dispatcher()
    {
        data.unlock(locked_data);
        ts_debug_only(next_batch_index = 0;);
    }


    template < typename T, class TDataType, class TMemInterface >
    T *lock_free_batch_dispatcher< T, TDataType, TMemInterface >::get_next_batch(size_t _requested_batch_size,
        size_t &_returned_batch_size)
    {
        assert(locked_data); // Data has been accessed without locking
        size_t current_batch_index = next_batch_index.fetch_add(_requested_batch_size);
        size_t array_size = data.size();
        if (current_batch_index < array_size)
        {
            _returned_batch_size = std::min(array_size - current_batch_index, _requested_batch_size);
            return locked_data + current_batch_index;
        }
        else
        {
            _returned_batch_size = 0;
            return nullptr;
        }
    }
}