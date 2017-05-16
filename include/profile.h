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

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{
    namespace profile
    {
        typedef std::chrono::time_point< std::chrono::high_resolution_clock > time_point;
        typedef std::chrono::high_resolution_clock clock;
        typedef std::chrono::microseconds time;

        /// <summary>
        /// Struct timer
        /// </summary>
        struct timer
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="timer"/> struct.
            /// </summary>
            /// <param name="_elapsedTime">The elapsed time.</param>
            timer(std::chrono::microseconds &_elapsedTime)
                : start(clock::now())
                , elapsedTime(_elapsedTime)
            {
            }

            /// <summary>
            /// Finalizes an instance of the <see cref="timer"/> class.
            /// </summary>
            ~timer()
            {
                elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - start);
            }

            /// <summary>
            /// The start
            /// </summary>
            time_point start;
            /// <summary>
            /// The elapsed time
            /// </summary>
            time &elapsedTime;
        };

        /// <summary>
        /// Instruments the specified profile time.
        /// </summary>
        /// <param name="_profileTime">The profile time.</param>
        /// <param name="_classType">Type of the class.</param>
        /// <param name="_func">The function.</param>
        /// <param name="..._params">The ... parameters.</param>
        /// <returns>TReturnType.</returns>
        template < typename TReturnType, typename TClassType, typename TMemFunc, typename... TArgs >
        TReturnType instrument(time &_profileTime, TClassType *_classType, TMemFunc _func, TArgs... _params)
        {
            timer profile_timer(_profileTime);
            return (_classType->*_func)(std::forward< TArgs >(_params)...);
        }

        /// <summary>
        /// Class profile_mem_interface.
        /// </summary>
        class profile_mem_interface
        {

        };

        class errors
        {
        public:
#if TASK_SCHEDULER_ENABLE_ITT != 0
            enum type : unsigned int {
                threads = __itt_suppress_threading_errors,
                memory = __itt_suppress_memory_errors,
                all = __itt_suppress_all_errors
            };
#else
            enum type {
                threads,
                memory,
                all
            };
#endif

            inline static void suppress(enum type _error)
            {
                ts_itt(__itt_suppress_push((unsigned int)_error););
                stack.push_front(_error);
            }

            inline static void unsuppress(enum type _error)
            {
                enum type stack_item;
                stack.pop_front(stack_item);
                ts_assert(stack_item == _error);
                ts_itt(__itt_suppress_pop(););
            }

        private:
            typedef lock_free_node_dispenser< enum type, profile_mem_interface > memory_allocator_type;
            typedef lock_free_stack< enum type, profile_mem_interface, memory_allocator_type > stack_type;
            static memory_allocator_type dispenser;
            static stack_type stack;
        };

        inline void suppress()
        {
            errors::suppress(errors::all);
        }

        inline void unsuppress()
        {
            errors::unsuppress(errors::all);
        }

        class memory : public errors
        {
        public:

            static memory* create_instance(const tchar_t* _name, tchar_t* _domain);

            static void suppress()
            {
                errors::suppress(errors::memory);
            }

            static void unsuppress()
            {
                errors::unsuppress(errors::memory);
            }

            virtual void allocate_begin(size_t _size, bool _initialized) {}

            virtual void allocate_end(void** _memory_allocation, size_t _size, bool _initialized) {}

        };

#if TASK_SCHEDULER_ENABLE_ITT != 0
        class memory_itt : public memory
        {
        public:
            memory_itt(const tchar_t* _name, tchar_t* _domain)
            {
                m_Heap = __itt_heap_function_create(_name, _domain);
            }

            void allocate_begin(size_t _size, bool _initialized) override
            {
                __itt_heap_allocate_begin(m_Heap, _size, _initialized ? 1 : 0);
            }

            void allocate_end(void** _memory_allocation, size_t _size, bool _initialized) override
            {
                __itt_heap_allocate_end(m_Heap, _memory_allocation, _size, _initialized ? 1 : 0);
            }

        private:
            __itt_heap_function m_Heap;
        };
#endif

        memory* memory::create_instance(const tchar_t* _name, tchar_t* _domain)
        {
            ts_itt(return new memory_itt(_name, _domain));
        }

        namespace thread
        {
            inline void set_name(const tchar_t* _name)
            {
                ts_itt(__itt_thread_set_name(_name););
            }

            inline void suppress()
            {
                errors::suppress(errors::threads);
            }

            inline void unsuppress()
            {
                errors::unsuppress(errors::threads);
            }

        }

    }
}