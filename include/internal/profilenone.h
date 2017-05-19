// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="profilenone.h" >
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
 
#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_NONE
        class basic_errors
        {
        public:
            inline void suppress(enum errors::type _error)
            {
                ts_unused(_error);
            }

            inline void unsuppress(enum errors::type _error)
            {
                ts_unused(_error);
            }
        };

        static errors* instance()
        {
            static error_stack<basic_errors> error_instance;
            return &error_instance;
        }

        template<class TKey>
        memory* memory::instance()
        {
            ts_always_assert();
            return nullptr;
        }
#endif

    }

}