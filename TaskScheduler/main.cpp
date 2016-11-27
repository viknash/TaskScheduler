#include "stdafx.h"

#include <algorithm>
#include <random>

#include "containers.h"
#include "profile.h"
#include "task.h"
#include "taskgraph.h"
#include "thread.h"
#include "threadpool.h"
#include "utils.h"

using namespace task_scheduler;
using namespace std;

default_mem_interface gDefaultMemInterface;

void* operator new(size_t n)
{
    //DebugBreak();
    return gDefaultMemInterface.operator new(n);
}
void operator delete(void* p, size_t n)
{
    //DebugBreak();
    gDefaultMemInterface.operator delete(p, n);
}

void* operator new[](size_t n)
{
    //DebugBreak();
    return gDefaultMemInterface.operator new[](n);
}

void operator delete[](void* p, size_t n)
{
    // DebugBreak();
    gDefaultMemInterface.operator delete[](p, n);
}

template <>
thread_local base_thread<default_mem_interface>* base_thread_pool<default_mem_interface>::current_thread = nullptr;

void RandomTimeTask(chrono::milliseconds minTaskTime, chrono::milliseconds maxTaskTime)
{
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = end = chrono::high_resolution_clock::now();
    uint64_t minTaskTimeMs = chrono::microseconds(minTaskTime).count();
    uint64_t maxTaskTimeMs = chrono::microseconds(maxTaskTime).count();

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(minTaskTimeMs, maxTaskTimeMs);
    uint64_t randomTime = dis(gen);
    chrono::microseconds randomTimeUS(randomTime);

    while (end - start < randomTimeUS) {
        end = chrono::high_resolution_clock::now();
    }
}

int main()
{
    typedef base_task_graph<default_mem_interface> task_graph_type;
    typedef base_thread_pool<default_mem_interface> thread_pool;

    thread_pool pool(128);
    task_graph_type task_graph(pool);
    task_graph.load("tasks.txt");

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(0, 63);
    for (auto& task : task_graph.debug.task_list) {
        task->persistent.run_functor = bind(RandomTimeTask, 1ms, 16ms);
        task->set_thread_affinity(CreateMask64(dis(gen), dis(gen), dis(gen)));
    }

    pool.start(task_graph);
    task_graph.kick();
    this_thread::sleep_for(30s);
    pool.end();
    system("pause");
    return 0;
}
