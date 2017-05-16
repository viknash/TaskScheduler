// ***********************************************************************
// <copyright file="lockfreenodedispenser.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>

#include "atomics.h"
#include "lockfreenode.h"

namespace task_scheduler {


    template < typename T, class TMemInterface >
    class lock_free_node_dispenser : public TMemInterface
    {
        typedef lock_free_node< T, TMemInterface > node_type;
        typedef lock_free_node_stack< T, TMemInterface > node_stack;
        typedef std::vector< node_type, stl_allocator< T, TMemInterface > > node_vector;

    public:
        lock_free_node_dispenser(uint32_t _start_count = 0)
        {
            if (_start_count)
            {
                // Array requested
                array.reserve(_start_count);
                while (_start_count--)
                {
                    dispenser.push_front(&array[_start_count]);
                }
            }
        }

        ~lock_free_node_dispenser()
        {
            if (!array.size())
            {
                lock_free_node< T, TMemInterface > *node = dispenser.pop_front();
                while (node)
                {
                    delete (node);
                    node = dispenser.pop_front();
                }
            }
        }

        inline node_type *new_node()
        {
            node_type *ret = dispenser.pop_front();
            if (ret == nullptr)
            {
                if (!array.size())
                {
                    ret = new node_type();
                }
                else
                {
                    ts_print("Insufficient number of pre-allocated Nodes");
                }
            }

            ts_debug_only(ret->next.node = nullptr;);
            return ret;
        }

        inline void free_node(node_type *_node)
        {
            assert(_node->next.node == nullptr);
            dispenser.push_front(_node);
        }

    private:
        node_stack dispenser;
        node_vector array;
    };
}