// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="profilebase.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "../platform.h"

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

            template<class TInterface, class TKey = TInterface>
            friend TInterface* get();

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
            ts_declare_attribute_and_callbacks(memory, const tchar_t*, name);

            memory()
                : ts_init_attribute_and_callbacks(memory, name, _t(""))
            {}

            void suppress()
            {
                get<errors>()->suppress(errors::type::memory);
            }

            void unsuppress()
            {
                get<errors>()->unsuppress(errors::memory);
            }

            virtual void allocate_begin(size_t _size, bool _initialized) {
                ts_unused(_size); ts_unused(_initialized);
            }

            virtual void allocate_end(void** _memory_allocation, size_t _size, bool _initialized) {
                ts_unused(_memory_allocation); ts_unused(_size); ts_unused(_initialized);
            }

            template <class TKey>
            static memory* instance();
        };


        void memory::set_name(const tchar_t* _name)
        {
            *&name = _name;
        }

        const tchar_t* memory::get_name()
        {
            return (&name)->c_str();
        }

        namespace thread
        {

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

        template <class TStringImplementation>
        class basic_string : public TStringImplementation
        {
        public:

            basic_string(const tchar_t* _name)
                : TStringImplementation(_name)
            {
            }

            typename TStringImplementation::handle& operator* ()
            {
                return TStringImplementation::operator*();
            }

        };

        class domain
        {
        public:
            typedef void* handle;

            ts_declare_attribute_and_callbacks(domain, const tchar_t*, name);
        
            domain()
                : ts_init_attribute_and_callbacks(domain, name, _t(""))
                , hdl(nullptr)
            {}

            virtual handle operator* () { return hdl; }

            template <class TKey>
            static domain* instance();
        private:
            handle hdl;
        };

        void domain::set_name(const tchar_t* _name)
        {
            *&name = _name;
        }

        const tchar_t* domain::get_name()
        {
            return (&name)->c_str();
        }

        class function
        {
            typedef void* handle;
        public:
            template <class TFuncType>
            function(TFuncType _func)
                : function_ptr((void*)_func)
            {
            }

            typename handle& operator* ()
            {
                return function_ptr;
            }

        private:
            void* function_ptr;
        };


    }

}