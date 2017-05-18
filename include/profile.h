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
            enum type {
                threads = 0,
                memory,
                all
            };

            virtual void suppress(enum type _error) = 0;
            virtual void unsuppress(enum type _error) = 0;

            template<class TInterface> friend TInterface* get();

        private:

            static errors* instance();
        };

        template <class TErrorImplementation>
        class error_stack : public errors
        {
            typedef lock_free_node_dispenser< enum type, profile_mem_interface > memory_allocator_type;
            typedef lock_free_stack< enum type, profile_mem_interface, memory_allocator_type > stack_type;

        public:

            void suppress(enum type _error) override
            {
                error_implementation.suppress(_error);
                stack.push_front(_error);
            }

            void unsuppress(enum type _error) override
            {
                enum type stack_item;
                stack.pop_front(stack_item);
                ts_assert(stack_item == _error);
                error_implementation.unsuppress(_error);
            }

        private:
            stack_type stack;
            memory_allocator_type dispenser;
            TErrorImplementation error_implementation;
        };


        class memory
        {
        public:

            static memory* allocate();

            static void deallocate(memory* _instance);

            memory()
                : data(nullptr)
            {}

            void set_user_data(void* _data)
            {
                data = _data;
            }

            void* get_user_data()
            {
                return data;
            }

            void suppress()
            {
                get<errors>()->suppress(errors::type::memory);
            }

            void unsuppress()
            {
                get<errors>()->unsuppress(errors::memory);
            }

            virtual void set_name(const tchar_t* _name, tchar_t* _domain) {
                ts_unused(_name); ts_unused(_domain);
            }

            virtual void allocate_begin(size_t _size, bool _initialized) {
                ts_unused(_size); ts_unused(_initialized);
            }

            virtual void allocate_end(void** _memory_allocation, size_t _size, bool _initialized) {
                ts_unused(_memory_allocation); ts_unused(_size); ts_unused(_initialized);
            }

        private:
            void* data;
        };

        namespace thread
        {
            inline void set_name(const tchar_t* _name)
            {
                ts_itt(__itt_thread_set_name(_name););
            }

            inline void suppress()
            {
                get<errors>()->suppress(errors::threads);
            }

            inline void unsuppress()
            {
                get<errors>()->unsuppress(errors::threads);
            }

        }

        inline void suppress()
        {
            get<errors>()->suppress(errors::all);
        }

        inline void unsuppress()
        {
            get<errors>()->unsuppress(errors::all);
        }

#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_NONE
        class basic_errors
        {
        public:
            inline void suppress(enum type _error)
            {
                (void)_error;
            }

            inline void unsuppress(enum type _error)
            {
                (void)_error;
            }
        };

        static errors* instance()
        {
            static error_stack<basic_errors> error_instance;
            return &error_instance;
        }

        memory* memory::allocate()
        {
            return nullptr;
        }
#endif

        void deallocate(memory* _instance)
        {
            delete _instance;
        }

    }

}