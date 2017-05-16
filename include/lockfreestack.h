// ***********************************************************************
// <copyright file="lockfreestack.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>

#include "atomics.h"
#include "lockfreenode.h"

namespace task_scheduler {

    template<typename T, class TMemInterface, class TDispenser >
    class lock_free_stack
    {
        typedef lock_free_node< T, TMemInterface > node_type;
        typedef lock_free_node_stack< T, TMemInterface > node_stack_type;
        typedef lock_free_stack< T, TMemInterface, TDispenser > stack_type;

    public:
        inline lock_free_stack(TDispenser* _dispenser = nullptr);
        inline ~lock_free_stack();

        inline void push_front(const T& _value);

        bool pop_front(T& _out);

        inline bool empty();

    private:

        node_stack_type  stack;
        TDispenser* dispenser;
    };

    template<typename T, class TMemInterface, class TDispenser >
    lock_free_stack<T, TMemInterface, TDispenser>::lock_free_stack(TDispenser *_dispenser)
        : dispenser(_dispenser)
    {

    }

    template<typename T, class TMemInterface, class TDispenser >
    lock_free_stack<T, TMemInterface, TDispenser>::~lock_free_stack()
    {
        T temp;
        while (pop_front(temp) == true) {}
    }

    template<typename T, class TMemInterface, class TDispenser >
    void lock_free_stack<T, TMemInterface, TDispenser>::push_front(const T& _value)
    {
        node_type* node = dispenser->new_node();
        node->store(_value);
        stack.push_front(node);
    }

    template<typename T, class TMemInterface, class TDispenser >
    bool lock_free_stack<T, TMemInterface, TDispenser>::pop_front(T& _out)
    {
        node_type* node;
        node = stack.pop_front();

        if (!node)
            return false;

        _out = node->load();
        dispenser->free_node(node);

        return true;
    }

    template<typename T, class TMemInterface, class TDispenser >
    bool lock_free_stack<T, TMemInterface, TDispenser>::empty()
    {
        return stack.empty();
    }

}