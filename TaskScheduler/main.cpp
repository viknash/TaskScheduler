// Practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "containers.h"
#include "task.h"
#include "taskgraph.h"
#include "threadpool.h"
#include "profile.h"

template <> thread_local BaseThreadPool<DefaultMemInterface>::ThreadData* BaseThreadPool<DefaultMemInterface>::threadData;

void RandomTimeTask(chrono::milliseconds minTaskTime, chrono::milliseconds maxTaskTime)
{
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = end = chrono::high_resolution_clock::now();
    uint64_t minTaskTimeMs = chrono::microseconds(minTaskTime).count();
    uint64_t maxTaskTimeMs = chrono::microseconds(maxTaskTime).count();


    random_device rd;
    mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(minTaskTimeMs, maxTaskTimeMs);
    uint64_t randomTime = dis(gen);
    chrono::microseconds randomTimeUS(randomTime);

    while(end - start < randomTimeUS)
    {
        end = chrono::high_resolution_clock::now();
    }

}

int main()
{
    typedef BaseTaskGraph<DefaultMemInterface> TaskGraph;
    typedef BaseThreadPool<DefaultMemInterface> ThreadPool;

    ThreadPool pool;
    TaskGraph taskGraph(pool);
    taskGraph.Load("tasks.txt");

    for (auto& task : taskGraph.debug.taskList)
    {
        task->runFunctor = bind(RandomTimeTask, 1ms, 16ms);
    }

    pool.Start(taskGraph);
    taskGraph.Kick();
    this_thread::sleep_for(5s);
    pool.End();
    system("pause");
    return 0;
}


