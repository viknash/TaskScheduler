// ***********************************************************************
// <copyright file="lockfreequeue.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>

#include "atomics.h"
#include "lockfreenode.h"

namespace task_scheduler {

    // Multi Producer Multi Consumer Lock-free queue implementation
    // Elements are contained into single-chained nodes provided by a lock_free_node_dispenser.
    // param T Name of the type of object in the container

    template < typename T, class TMemInterface, class TDispenser > class multi_producer_multi_consumer
    {
        typedef lock_free_node< T, TMemInterface > node_type;
        typedef atomic_lock_free_node< T, TMemInterface > atomic_node;
        typedef atomic_lock_free_node_ptr< T, TMemInterface > atomic_node_ptr;

    public:
        multi_producer_multi_consumer(TDispenser *_dispenser = 0)
            : dispenser(_dispenser)
        {
            end_node.node = (node_type *)(this); // Magic Value for the end node
            ts_debug_only(debug.counter = 1);
            node_type *sentinelle = dispenser->new_node();
            head.data.points_to.node = sentinelle;
            head.data.access.as_atomic = 0;
            tail.data.points_to.node = sentinelle;
            tail.data.access.as_atomic = 0;
            sentinelle->next.node = end_node.node;
        }

        ~multi_producer_multi_consumer()
        {
            clear();
            assert(head.data.points_to.node == tail.data.points_to.node);
            assert(head.data.points_to.node->next.node == end_node.node); // Check if list is empty
            ts_debug_only(head.data.points_to.node->next.node = nullptr;)
                dispenser->free_node(head.data.points_to.node);
        }

        /*! Add an object in the queue
        \param _value Object to add
        */
        inline bool push_back(const T &_value)
        {
            atomic_node new_node;
            new_node.node = dispenser->new_node();
            new_node.node->store(_value);
            assert(new_node.node->next.node == nullptr);
            new_node.node->next.node = end_node.node;

            atomic_node_ptr tail_snapshot;
            tail_snapshot = tail;
            ts_debug_only(atomics::increment(debug.counter););
            while (end_node.as_atomic != atomics::compare_exchange_weak(tail.data.points_to.node->next.as_atomic,
                end_node.as_atomic, new_node.as_atomic))
            {
                ts_debug_only(atomics::decrement(debug.counter););
                update_tail(tail_snapshot);
                tail_snapshot = tail;
                ts_debug_only(atomics::increment(debug.counter););
            }

            // If the tail remains the same then update the tail
            atomic_node_ptr newTail;
            newTail.data.access.as_atomic = tail_snapshot.data.access.as_atomic + 1;
            newTail.data.points_to.node = new_node.node;
            tail.compare_exchange_weak(tail_snapshot, newTail);

            return true;
        }

        inline bool peek(T &_out)
        {
            T value = T();
            atomic_node_ptr headSnapshot;
            node_type *nextSnapshot;
            bool ret = true;
            bool skip = false;

            do
            {
                skip = false;
                headSnapshot = head;
                nextSnapshot = headSnapshot.data.points_to.node->next;

                if (headSnapshot.data.access != head.data.access)
                {
                    skip = true;
                    continue;
                }

                if (nextSnapshot == end_node.node)
                {
                    _out = T();
                    ret = false;
                    break;
                }

                ts_debug_only(if (!nextSnapshot) continue;);
                value = nextSnapshot->load();

            } while (skip || !head.compare_exchange_weak(headSnapshot, headSnapshot));

            _out = value;

            return ret;
        }

        inline bool pop_front(T &_out)
        {
            node_type *node = internal_remove();
            if (node == nullptr)
                return false;

            _out = node->load();
            dispenser->free_node(node);

            return true;
        }

        // Returns true if the queue is empty
        inline bool empty() const { return head.data.points_to.node->next.node == end_node.node; }

        // Remove all objects from the queue.
        void clear()
        {
            node_type *node = internal_remove();
            while (node)
            {
                dispenser->free_node(node);
                node = internal_remove();
            }
        }

    private:
        inline void update_tail(atomic_node_ptr &_tail)
        {
            atomic_node_ptr newTail;
            newTail.data.access.as_atomic = _tail.data.access.as_atomic + 1;
            newTail.data.points_to.node = _tail.data.points_to.node->next.node;
            if (newTail.data.points_to.node != end_node.node)
            {
                tail.compare_exchange_weak(_tail, newTail);
            }
        }

        node_type *internal_remove()
        {
            T value = T();
            atomic_node_ptr ptr_head, ptr_tail, new_head;
            node_type *ptr_next;
            bool success = true;
            bool skip = false;

            do
            {
                skip = false;
                // Save a local copy of pointers to update them locally
                ptr_head = head;
                ptr_next = ptr_head.data.points_to.node->next.node;
                ptr_tail = tail;

                // Early abort and retry if some other thread has already modified the head
                if (ptr_head.data.access.as_atomic != head.data.access.as_atomic)
                {
                    skip = true;
                    continue;
                }

                // Abort if head points to the sentinelle
                if (ptr_next == end_node.node)
                {
                    ptr_head.data.points_to.node = nullptr;
                    success = false;
                    break;
                }

                // Early abort and retry if the queue is empty
                if (ptr_head.data.points_to.node == ptr_tail.data.points_to.node)
                {
                    // Update tail for the next retry as it could have changed
                    update_tail(ptr_tail);
                    skip = true;
                    continue;
                }

                ts_debug_only(if (!ptr_next) continue;);
                // Save the value to be return if this try is successful
                value = ptr_next->load();

                // Assemble a new head
                new_head.data.access.as_atomic = ptr_head.data.access.as_atomic + 1;
                new_head.data.points_to.node = ptr_next;

                // if the head we worked is the same as the current head, replace it with a new head
            } while (skip || !head.compare_exchange_weak(ptr_head, new_head));

            if (success)
            {
                assert(atomics::decrement(debug.counter));
            }

            // If we succeeded then return the new value the removed node
            if (ptr_head.data.points_to.node != nullptr)
            {
                ptr_head.data.points_to.node->store(value);
                ts_debug_only(ptr_head.data.points_to.node->next.node = nullptr;);
            }

            return ptr_head.data.points_to.node;
        }

    private:
        atomic_node_ptr volatile head;
        atomic_node_ptr volatile tail;
        atomic_node end_node;
        TDispenser *dispenser;
        struct debug_container
        {
            volatile int32_t counter;
        };
        ts_debug_only(debug_container debug;);
    };

    template < class TPolicy, class T, class TMemInterface, class TParam = void * >
    class lock_free_queue : public TMemInterface
    {
    public:
        lock_free_queue() {}

        lock_free_queue(TParam param)
            : queue(param)
        {
        }

        virtual bool push_back(T newData) { return queue.push_back(newData); }

        //virtual bool push_front(T newData) { return queue.push_front(newData); }

        virtual bool pop_front(T &val) { return queue.pop_front(val); }

        virtual bool pop_back(T &val) { return queue.pop_front(val); }

        virtual bool empty() const { return queue.empty(); }

        virtual ~lock_free_queue() {}

        TPolicy queue;
    };

}