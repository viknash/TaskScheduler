// ***********************************************************************
// <copyright file="lockfreenodestack.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>

#include "atomics.h"
#include "lockfreenode.h"

namespace task_scheduler {
    template < typename T, class TMemInterface > class class_alignment lock_free_node_stack : public TMemInterface
    {
        typedef lock_free_node< T, TMemInterface > node_type;
        typedef atomic_lock_free_node_ptr< T, TMemInterface > atomic_node_ptr;

    public:
        lock_free_node_stack()
        {
            head.clear();
            ts_debug_only(debug.counter = 0;);
        }

        void push_front(node_type *_node)
        {
            ts_debug_only(assert(_node->next.node == nullptr););
            atomic_node_ptr copy, newNode;
            do
            {
                copy = head;
                newNode.data.access.as_atomic = copy.data.access.as_atomic + 1;
                newNode.data.points_to.node = _node;
                _node->next.node = head.data.points_to.node;
            } while (!head.compare_exchange_weak(copy, newNode));
            ts_debug_only(atomics::increment(debug.counter););
        }

        node_type *pop_front()
        {
            atomic_node_ptr copy, inc_copy;
            do
            {
                copy = head;
                if (copy.data.points_to.node == nullptr)
                {
                    return nullptr;
                }

                inc_copy.data.access.as_atomic = copy.data.access.as_atomic + 1;
                inc_copy.data.points_to.node = copy.data.points_to.node->next.node;

            } while (!head.compare_exchange_weak(copy, inc_copy));

            ts_debug_only(atomics::decrement(debug.counter););
            ts_debug_only(copy.data.points_to.node->next.node = nullptr;);
            return copy.data.points_to.node;
        }

        bool empty() { return head.data.points_to.node == nullptr; }

        ~lock_free_node_stack()
        {}

    private:
        atomic_node_ptr head;

        struct debug_container
        {
            int32_t counter;
        };
        ts_debug_only(debug_container debug;);
    };
}