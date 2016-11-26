#pragma once

#include "containers.h"
#include "meta.h"
#include "profile.h"

template <class MemInterface>
class BaseTask;
template <class MemInterface>
class BaseTaskGraph;
template <class MemInterface>
class BaseThreadPool;
template <class MemInterface>
struct BaseThread;

template <class MemInterface>
class BaseThreadPool {
    typedef typename BaseThread<MemInterface> Thread;
    typedef typename BaseTaskGraph<MemInterface> TaskGraph;
    typedef typename TaskGraph::Task Task;
    typedef typename TaskGraph::TaskQueue TaskQueue;
    typedef typename TaskGraph::TaskMemoryAllocator TaskMemoryAllocator;
    typedef typename BaseThreadPool<MemInterface> ThreadPool;

public:
    enum State {
        Run = 0,
        RequestPause,
        RequestStop
    };

    struct Setup {
        mutex signal;
        condition_variable radio;
        atomic<uint32_t> threadSync;
        atomic<State> requestExit;
    };

public:
    BaseThreadPool(uint32_t _numThreads = MAX_NUM_THREADS);
    void Start(TaskGraph& taskGraph);
    void End();
    void Wakeup(uint8_t numThreadsToWakeup = MAX_NUM_THREADS);

    static const uint32_t MAX_NUM_THREADS = 64;

    Setup setup;
    uint8_t numThreads;
    TaskGraph* taskGraph;
    Thread* threads[MAX_NUM_THREADS];
    TaskMemoryAllocator taskMemoryAllocator;
    atomic<uint32_t> numWorking;

    optimization atomic<typename Task::Rank> queueRank[Task::NUM_PRIORITY][MAX_NUM_THREADS];

    thread_local static Thread* currentThread;
};

template <class MemInterface>
BaseThreadPool<MemInterface>::BaseThreadPool(uint32_t _numThreads)
    : numThreads(min(min(thread::hardware_concurrency(), MAX_NUM_THREADS), _numThreads))
    , taskGraph(nullptr)
{
    memset(threads, 0, sizeof(threads));
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Start(TaskGraph& _taskGraph)
{
    taskGraph = &_taskGraph;
    setup.threadSync.store(uint32_t(numThreads));

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++) {
        threads[threadIdx] = Thread::CreateThread(this);
    }

    //Wait until all threads are started
    while (setup.threadSync != 0) {
        unique_lock<mutex> signal(setup.signal);
        setup.radio.wait(signal);
    }

    //Kick all sleeping threads
    Wakeup();
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::End()
{
    setup.threadSync = (uint32_t)taskGraph->persistent.subGraphs.size();
    setup.requestExit.store(RequestPause);

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++) {
        threads[threadIdx]->Join();
    }

    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++) {
        delete threads[threadIdx];
    }

    memset(threads, 0, sizeof(threads));
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Wakeup(uint8_t numThreadsToWakeup)
{
    numThreadsToWakeup = min(numThreads, numThreadsToWakeup);
    reduce_starvation(always_different_thread_woken_up_first) static uint32_t nextThreadIndex = 0;
    for (uint32_t threadIdx = nextThreadIndex, iterations = 0; iterations < numThreadsToWakeup; threadIdx = (threadIdx + 1) % numThreads, iterations++) {
        threads[threadIdx]->Wakeup();
    }
    reduce_starvation(always_different_thread_woken_up_first) nextThreadIndex = (nextThreadIndex + 1) % numThreads;
}