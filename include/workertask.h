// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="workertask.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <atomic>
#include <cinttypes>
#include <vector>

#include "memory.h"
#include "meta.h"
#include "print.h"
#include "types.h"
#include "task.h"
namespace task_scheduler
{
    template < class TMemInterface > class base_worker_task : public base_task<TMemInterface>
    {
    public:
        typedef base_task<TMemInterface> super;
        typedef base_worker_task< TMemInterface > worker_task_type;

        /// <summary>
        /// Initializes a new instance of the <see cref="base_worker_task"/> class.
        /// </summary>
        /// <param name="_task_graph">The task graph.</param>
        base_worker_task(task_graph_type &_task_graph);
        /// <summary>
        /// Finalizes an instance of the <see cref="base_worker_task"/> class.
        /// </summary>
        ~base_worker_task();

    protected:
        /// <summary>
        /// Callback to run task
        /// </summary>
        bool run() override;

    private:
        /// <summary>
        /// Calls the working function internally
        /// </summary>
        /// <returns>bool.</returns>
        void run_internal(function_type* _work_function);
        /// <summary>
        /// Gets the best number of workers for the task every frame
        /// </summary>
        /// <param name="_num_workers">The number workers.</param>
        virtual thread_num_t get_recommended_num_workers() override;
    };

    template < class TMemInterface >
    base_worker_task< TMemInterface >::base_worker_task(task_graph_type &_task_graph)
        : super(_task_graph)
    {
    }

    template < class TMemInterface >
    base_worker_task< TMemInterface >::~base_worker_task()
    {
    }

    template < class TMemInterface >
    bool base_worker_task< TMemInterface >::run()
    {
        function_type *work_function = nullptr;
        while (!transient.work_queue->empty())
        {
            if (transient.work_queue->pop_front(work_function))
            {
                instrument< void, worker_task_type, void (worker_task_type::*)(function_type*) >(transient.task_time, this, &worker_task_type::run_internal, work_function);
                ++transient.num_runned;
            }
        }
        return transient.num_runned ? true : false;
    }

    template < class TMemInterface >
    void base_worker_task< TMemInterface >::run_internal(function_type* _work_function)
    {
        (*_work_function)();
    }

    template < class TMemInterface >
    thread_num_t base_worker_task< TMemInterface >::get_recommended_num_workers()
    {
        thread_num_t optimum_num_workers = thread_num_t(persistent.task_work.size() / transient.minimum_batch_size);
        return std::min(optimum_num_workers, persistent.num_workers);
    }

}

