// ***********************************************************************
// <copyright file="containers.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>

#include "atomics.h"

namespace task_scheduler {
    union address {
        volatile void *ptr;
        atomics::type as_atomic;
    };

    class dummy
    {

    };

    template < typename T, class TMemInterface > struct lock_free_node;

    template < typename T, class TMemInterface > struct atomic_lock_free_node : public TMemInterface
    {
        typedef lock_free_node< T, TMemInterface > node_type;
        union {
            node_type *volatile node;
            atomics::type as_atomic;
        };
    };
    //static_assert(sizeof(atomic_lock_free_node< void *, dummy >) == sizeof(address),
    //              "size of atomic_lock_free_node is incorrect.");

    template < typename T, class TMemInterface > struct class_alignment lock_free_node : public TMemInterface
    {
        typedef atomic_lock_free_node< T, TMemInterface > atomic_node;

        explicit operator void *() const { return reinterpret_cast<void *>(this); }

        inline lock_free_node() { next.node = nullptr; }
        inline const T &load() const { return value; }
        inline void store(const T &_value) { value = _value; }

        atomic_node next;
        T value;

        static_assert(sizeof(T) <= sizeof(address), "T must be a POD");
    };
    //static_assert(sizeof(lock_free_node< void *, dummy >) == sizeof(address) * 2,
    //              "size of atomic_lock_free_node is incorrect.");

    template < typename T, class TMemInterface > struct class_alignment atomic_lock_free_node_ptr : public TMemInterface
    {
        typedef atomic_lock_free_node< T, TMemInterface > atomic_node;
#pragma warning(push)
#pragma warning(disable : 4201)
        union Data {
            struct
            {
                atomic_node points_to;
                address access;
            };
            atomics::type as_atomic[2];

            Data() {}
            ~Data() {}
        };
#pragma warning(pop)
        inline void clear()
        {
            data.access.ptr = nullptr;
            data.points_to.node = nullptr;
        }

        inline bool compare_exchange_weak(atomic_lock_free_node_ptr &comperand,
            atomic_lock_free_node_ptr &value) volatile
        {
            return atomics::compare_exchange_weak_128(data.as_atomic, comperand.data.as_atomic,
                value.data.access.as_atomic, value.data.points_to.as_atomic);
        }

        void operator=(const volatile atomic_lock_free_node_ptr &other)
        {
            data.access.as_atomic = other.data.access.as_atomic;
            data.points_to.node = other.data.points_to.node;
        }

        atomic_lock_free_node_ptr() {};
        ~atomic_lock_free_node_ptr() {};

        Data data;
    };
    static_assert(sizeof(atomic_lock_free_node_ptr< bool, dummy >) == sizeof(address) * 2,
                  "size of atomic_lock_free_node_ptr is incorrect.");
}