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
                ts_unused(_error);
                __itt_suppress_pop();
            }
            
        };

        template <class TKey>
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

        template< typename TKey>
        memory* memory::instance()
        {
            static memory_itt memory;
            return &memory;
        }

        class domain_itt : public domain
        {
            typedef domain super;
        public:
            void set_name(const tchar_t* _name)
            {
                super::set_name(_name);
                itt_domain = __itt_domain_create(_name);
            }

            super::handle& operator* () override { 
                return (super::handle&)itt_domain;
            }

        private:
            __itt_domain* itt_domain;
        };

        template <class TKey>
        static domain* domain::instance()
        {
            static domain_itt domain;
            return &domain;
        }

        class itt_string
        {
        public:
            typedef __itt_string_handle* handle;

            itt_string(const tchar_t* _name)
            {
                string_handle = __itt_string_handle_create(_name);
            }

            typename handle& operator* ()
            {
                return string_handle;
            }
        private:
            __itt_string_handle* string_handle;
        };

        typedef basic_string<itt_string> string;

        class id
        {
            typedef __itt_id handle;
        public:
            id(const tchar_t* _name)
                : itt_id(__itt_null)
            {
                itt_id = __itt_id_make((void*)_name, thread_unique_number);
                __itt_id_create(*get<domain>, itt_id);
            }

            typename handle& operator* ()
            {
                return itt_id;
            }

        private:
            __itt_id itt_id;
        };

        class function
        {
            typedef void* handle;
        public:
            template <class TFuncType>
            function(TFuncType _func)
                : function_ptr((void*) _func)
            {
            }

            typename handle& operator* ()
            {
                return function_ptr;
            }

        private:
            void* function_ptr;
        };

        struct task_param
        {
            function function;
            id task_id;
            id parent_task_id;
            string task_name;
        };

        class task
        {

        public:

            task()
            {
            }

            bool enter(task_param& _param)
            {
                if (*_param.function)
                {
                    __itt_task_begin_fn(*get<domain>, *_param.task_id, *_param.parent_task_id, *_param.function);
                }
                else
                {
                    __itt_task_begin(*get<domain>, *_param.task_id, *_param.parent_task_id, *_param.task_name);
                }
                return true;
            }

            bool exit(task_param& param)
            {
                __itt_task_end(*get<profile::domain>);
                return true;
            }
        };

        typedef scoped_enter_exit< task, task_param > task_scoped_instrument;

#endif

    }
}