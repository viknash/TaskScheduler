// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="main.cpp" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "stdafx.h"

#include "platform.h"
#include <algorithm>
#include <cinttypes>
#include <random>

#include "containers.h"
#include "profile.h"
#include "task.h"
#include "taskgraph.h"
#include "thread.h"
#include "threadpool.h"
#include "utils.h"

#include "common/taskgraphhelper.h"

using namespace task_scheduler;
using namespace std;

task_scheduler_default_mem_interface_catch_all_allocations();
task_scheduler_static_data();

/// <summary>
/// Randoms the time task.
/// </summary>
/// <param name="minTaskTime">The minimum task time.</param>
/// <param name="maxTaskTime">The maximum task time.</param>
void RandomTimeTask(chrono::milliseconds minTaskTime, chrono::milliseconds maxTaskTime)
{
    chrono::time_point< chrono::high_resolution_clock > start, end;
    start = end = chrono::high_resolution_clock::now();
    uint64_t minTaskTimeMs = chrono::microseconds(minTaskTime).count();
    uint64_t maxTaskTimeMs = chrono::microseconds(maxTaskTime).count();

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution< uint64_t > dis(minTaskTimeMs, maxTaskTimeMs);
    uint64_t randomTime = dis(gen);
    chrono::microseconds randomTimeUS(randomTime);

    while (end - start < randomTimeUS)
    {
        end = chrono::high_resolution_clock::now();
    }
}

/// <summary>
/// Mains this instance.
/// </summary>
/// <returns>int.</returns>
int main()
{
    typedef base_task_graph< default_mem_interface > task_graph_type;
    typedef base_task_graph_helper< default_mem_interface > task_graph_helper_type;
    typedef base_thread_pool< default_mem_interface > thread_pool;

    thread_pool pool(128);
    task_graph_type task_graph(pool);
    task_graph_helper_type task_graph_helper(task_graph);
    task_graph_helper.load("tasks.txt");

    guarded_vector< void *, default_mem_interface > vector;
    {
        lock_free_batch_dispatcher< void *, guarded_vector< void *, default_mem_interface >, default_mem_interface >
            dispatcher(vector);
    }
    vector.push_back(nullptr);

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution< uint64_t > dis(0, 63);
    for (auto &task : task_graph.debug.task_list)
    {
        task->add_task_parallel_work(bind(RandomTimeTask, 1ms, 16ms));
        task->set_thread_affinity(create_mask_64(dis(gen), dis(gen), dis(gen)));
    }

    pool.start(task_graph);
    task_graph.kick();
    this_thread::sleep_for(30s);
    pool.stop();
    system("pause");
    return 0;
}
