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

        class memory;

#if TASK_SCHEDULER_ENABLE_ITT != 0
        class memory_itt : private memory
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
                __itt_heap_allocate_end(_heap, _memory_allocation, _size, _initialized ? 1 : 0);
            }

        private:
            __itt_heap_function m_Heap;
        };
#endif

        class memory
        {
        public:

            static memory* create_instance(const tchar_t* _name, tchar_t* _domain)
            {
                ts_itt(return new memory_itt(_name, _domain));
            }

            virtual void allocate_begin(size_t _size, bool _initialized) {}

            virtual void heap_allocate_end(void** _memory_allocation, size_t _size, bool _initialized) {}

        };

    }
}