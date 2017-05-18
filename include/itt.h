// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="profile.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <thread>

#include "utils.h"
#include "containers.h"
#include "profile.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{
    namespace profile {

#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_ITT
        class itt_errors
        {
        public:

            uint32_t get_itt_error(enum errors::type _error)
            {
                switch (_error)
                {
                case errors::threads:
                    return __itt_suppress_threading_errors;
                case errors::memory:
                    return __itt_suppress_memory_errors;
                case errors::all:
                    return __itt_suppress_all_errors;
                }
            }

            inline void suppress(enum errors::type _error)
            {
                __itt_suppress_push((unsigned int)get_itt_error(_error));
            }

            inline void unsuppress(enum errors::type _error)
            {
                (void)_error;
                __itt_suppress_pop();
            }
            
        };


        static errors* instance()
        {
            static error_stack<itt_errors> error_instance;
            return &error_instance;
        }

        class memory_itt : public memory
        {
        public:

            void set_name(const tchar_t* _name, tchar_t* _domain) override
            {
                heap = __itt_heap_function_create(_name, _domain);
            }

            void allocate_begin(size_t _size, bool _initialized) override
            {
                __itt_heap_allocate_begin(heap, _size, _initialized ? 1 : 0);
            }

            void allocate_end(void** _memory_allocation, size_t _size, bool _initialized) override
            {
                __itt_heap_allocate_end(heap, _memory_allocation, _size, _initialized ? 1 : 0);
            }

        private:
            __itt_heap_function heap;
        };

        memory* memory::allocate()
        {
            return new memory_itt();
        }

#endif

    }
}