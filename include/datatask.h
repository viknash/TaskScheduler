// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="datatask.h" >
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

    template < class TMemInterface, class TDataType > class base_data_task : public base_task<TMemInterface>
    {
        typedef base_data_task< TDataType, TMemInterface > data_task_type;
        typedef guarded_vector< TDataType, TMemInterface > data_vector;
        typedef lock_free_batch_dispatcher< TDataType*, guarded_vector< TDataType, TMemInterface >, TMemInterface > data_dispatcher_type;
        typedef base_task<TMemInterface> super;

        struct transient_data_container
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="base_task{TMemInterface}.transient_container"/> struct.
            /// </summary>
            transient_data_container(size_t _max_data_parallel_workload);
            /// <summary>
            /// Finalizes an instance of the <see cref="base_task{TMemInterface}.transient_container"/> class.
            /// </summary>
            ~transient_data_container();
            /// <summary>
            /// Total number of times work function was called
            /// </summary>
            data_vector data_workload;
            /// <summary>
            /// Data dispatcher for task work
            /// </summary>
            data_dispatcher_type *data_dispatcher;
            /// <summary>
            /// Calculated minimum batch size
            /// </summary>
            uint32_t minimum_batch_size;
        };

    public:
        /// <summary>
        /// The transient
        /// </summary>
        transient_data_container data_transient;
        /// <summary>
        /// Initializes a new instance of the <see cref="base_task"/> class.
        /// </summary>
        /// <param name="_task_graph">The task graph.</param>
        base_data_task(typename super::task_graph_type &_task_graph, size_t _max_data_parallel_workload = 0);
        /// <summary>
        /// Finalizes an instance of the <see cref="base_task"/> class.
        /// </summary>
        ~base_data_task();
        /// <summary>
        /// Add data parallel work class.
        /// </summary>
        /// <param name="_begin">Iterator to the start of a range of elements to add</param>
        /// <param name="_begin">Iterator to the end of a range of elements to add</param>
        bool add_data_parallel_work(typename data_vector::iterator _begin, typename data_vector::iterator _end);

    protected:
        /// <summary>
        /// Callback to run task
        /// </summary>
        bool run() override;
        /// <summary>
        /// Callback is called when a task is scheduled
        /// </summary>
        void before_scheduled(thread_num_t _scheduled_on_num_workers) override;
        /// <summary>
        /// Callback is called after a task is run
        /// </summary>
        void after_run() override;
        /// <summary>
        /// Gets the best number of workers for the task every frame
        /// </summary>
        /// <param name="_num_workers">The number workers.</param>
        virtual thread_num_t get_recommended_num_workers() override;

    private:
        /// <summary>
        /// Calls the working function internally
        /// </summary>
        /// <returns>bool.</returns>
        void run_internal(typename super::function_type* _work_function, TDataType& _data);
        /// <summary>
        /// The add task parallel work detector
        /// </summary>
        thread_unsafe_access_storage add_data_parallel_work_detector;
    };

    template < class TMemInterface, class TDataType >
    base_data_task< TMemInterface, TDataType >::transient_data_container::transient_data_container(size_t _max_data_parallel_workload)
        : data_workload(_max_data_parallel_workload)
        , data_dispatcher(nullptr)
    {
    }

    template < class TMemInterface, class TDataType >
    base_data_task< TMemInterface, TDataType >::transient_data_container::~transient_data_container()
    {
        assert(data_dispatcher == nullptr);
    }

    template < class TMemInterface, class TDataType >
    base_data_task< TMemInterface, TDataType >::base_data_task(typename super::task_graph_type &_task_graph, size_t _max_data_parallel_workload)
        : super(_task_graph)
        , data_transient(_max_data_parallel_workload)
    {
    }

    template < class TMemInterface, class TDataType >
    base_data_task< TMemInterface, TDataType >::~base_data_task()
    {
    }

    template < class TMemInterface, class TDataType >
    bool base_data_task< TMemInterface, TDataType >::add_data_parallel_work(typename data_vector::iterator _begin, typename data_vector::iterator _end)
    {
        thread_unsafe_access_guard guard(add_data_parallel_work_detector);
        assert(super::transient.num_working == 0);
        assert(super::persistent.task_work.size() <= 1);
        super::transient.data_workload.insert(_begin, _end);
    }

    template < class TMemInterface, class TDataType >
    bool base_data_task< TMemInterface, TDataType >::run()
    {
        assert(data_transient.data_workload.size());
        assert(!data_transient.data_workload.is_locked());
        typename super::function_type *work_function = nullptr;
        if (super::transient.work_queue->pop_front(this->work_function))
        {
            size_t available_batch_size = 0;
            TDataType* batch = data_transient.data_dispatcher->get_next_batch(data_transient.minimum_batch_size, available_batch_size);
            if (batch)
            {
                for (uint32_t batch_index; batch_index < available_batch_size; ++batch_index)
                {
                    instrument< void, data_task_type, void (data_task_type::*)(typename super::function_type*) >(super::transient.task_time, this, &data_task_type::run_internal, work_function, *(batch + batch_index));
                }
            }
            ++super::transient.num_runned;
            return true;
        }
        return false;
    }

    template < class TMemInterface, class TDataType >
    void base_data_task< TMemInterface, TDataType >::run_internal(typename super::function_type* _work_function, TDataType& _data)
    {
        (*_work_function)(_data);
    }

    template < class TMemInterface, class TDataType >
    void base_data_task< TMemInterface, TDataType >::before_scheduled(thread_num_t _scheduled_on_num_workers)
    {
        super::before_scheduled();

        assert(super::persistent.task_work.size() == 1); //Only supports one work function
        assert(super::transient.work_queue->empty());
        for (thread_num_t count = 0; count < _scheduled_on_num_workers; ++count)
        {
            super::transient.work_queue->push_back(super::persistent.task_work[0]);
        }

        if (data_transient.data_workload.size() && !data_transient.data_workload.is_locked())
        {
            assert(data_transient.data_dispatcher == nullptr);
            data_transient.data_dispatcher = new data_dispatcher_type(data_transient.data_workload);
        }
    }

    template < class TMemInterface, class TDataType >
    void base_data_task< TMemInterface, TDataType >::after_run()
    {
        super::after_run();
        assert(super::persistent.task_work.size() == 1); //Only supports one work function
        assert(super::transient.work_queue->empty());
        assert(super::transient.data_dispatcher);
        delete super::transient.data_dispatcher;
    }

    template < class TMemInterface, class TDataType >
    thread_num_t base_data_task< TMemInterface, TDataType >::get_recommended_num_workers()
    {
        size_t optimum_num_threads = data_transient.data_workload.size() / data_transient.minimum_batch_size;
        return std::min(super::persistent.num_workers, optimum_num_threads);
    }

}