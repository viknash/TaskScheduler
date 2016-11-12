#pragma once

#include "profile.h"
#include "containers.h"

template <class MemInterface> class BaseTask;
template <class MemInterface> class BaseTaskGraph;
template <class MemInterface> class BaseThreadPool;
template <class MemInterface> struct BaseThread;

template <class MemInterface>
class BaseThreadPool
{
    typedef typename BaseThread<MemInterface> Thread;
    typedef typename BaseTaskGraph<MemInterface> TaskGraph;
    typedef typename TaskGraph::Task Task;
    typedef typename TaskGraph::TaskQueue TaskQueue;
    typedef typename TaskGraph::TaskMemoryAllocator TaskMemoryAllocator;
    typedef typename BaseThreadPool<MemInterface> ThreadPool;

public:

    struct Setup
    {
        mutex signal;
        condition_variable radio;
        atomic<uint32_t> threadsNotStarted;
        atomic<bool> requestExit;
    };

public:

    BaseThreadPool();
    void Start(TaskGraph& taskGraph);
    void End();
    void Wakeup();

    static const uint32_t MAX_NUM_THREADS = 64;

    Setup               setup;
    uint8_t             numThreads;
    TaskGraph*          taskGraph;
    Thread*             threads[MAX_NUM_THREADS];
    TaskMemoryAllocator taskMemoryAllocator;

    optimization atomic<typename Task::Rank> queueRank[Task::NUM_PRIORITY][MAX_NUM_THREADS];

    thread_local static Thread* currentThread;
};

template <class MemInterface>
BaseThreadPool<MemInterface>::BaseThreadPool() :
    numThreads(0),
    taskGraph(nullptr)
{
    memset(threads, 0, sizeof(threads));
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Start(TaskGraph& _taskGraph)
{
    taskGraph = &_taskGraph;
    numThreads = min(thread::hardware_concurrency(), MAX_NUM_THREADS);
    setup.threadsNotStarted.store(uint32_t(numThreads));

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        threads[threadIdx] = Thread::CreateThread(this);
    }

    //Wait until all threads are started
    while (setup.threadsNotStarted != 0)
    {
        unique_lock<mutex> signal(setup.signal);
        setup.radio.wait(signal);
    }

    //Kick all sleeping threads
    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        threads[threadIdx]->Wakeup();
    }
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::End()
{
    setup.requestExit.store(true);

    Wakeup();

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        threads[threadIdx]->Join();
    }

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        delete threads[threadIdx];
    }

    memset(threads, 0, sizeof(threads));
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Wakeup()
{
    reduce_starvation(always_different_thread_woken_up_first) static uint32_t nextThreadIndex = 0;
    for (uint32_t threadIdx = nextThreadIndex, iterations = 0; iterations < numThreads; threadIdx = (threadIdx+1) % numThreads, iterations++ )
    {
        threads[threadIdx]->Wakeup();
    }
    reduce_starvation(always_different_thread_woken_up_first) nextThreadIndex = (nextThreadIndex + 1) % numThreads;
}