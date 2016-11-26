#include "containers.h"
#include "profile.h"
#include "stdafx.h"
#include "task.h"
#include "taskgraph.h"
#include "thread.h"
#include "threadpool.h"
#include "utils.h"

DefaultMemInterface gDefaultMemInterface;

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
thread_local BaseThread<DefaultMemInterface>* BaseThreadPool<DefaultMemInterface>::currentThread = nullptr;

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
    typedef BaseTaskGraph<DefaultMemInterface> TaskGraph;
    typedef BaseThreadPool<DefaultMemInterface> ThreadPool;

    ThreadPool pool(128);
    TaskGraph taskGraph(pool);
    taskGraph.Load("tasks.txt");

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(0, 63);
    for (auto& task : taskGraph.debug.taskList) {
        task->persistent.runFunctor = bind(RandomTimeTask, 1ms, 16ms);
        task->SetThreadAffinity(CreateMask64(dis(gen), dis(gen), dis(gen)));
    }

    pool.Start(taskGraph);
    taskGraph.Kick();
    this_thread::sleep_for(30s);
    pool.End();
    system("pause");
    return 0;
}
