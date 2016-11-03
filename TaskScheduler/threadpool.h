#pragma once

#include "profile.h"

template <class MemInterface> class BaseTask;
template <class MemInterface> class BaseTaskGraph;

template <class MemInterface>
class BaseThreadPool
{
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
    };

    struct ThreadData
    {
        ThreadData() :
            threadIndex(numeric_limits<uint8_t>::max())
        {
            for (auto& queue : taskQueue)
            {
                queue = new TaskQueue(&allocator);
            }
        }
        ~ThreadData()
        {
            for (auto& queue : taskQueue)
            {
                delete queue;
                queue = nullptr;
            }
        }
        TaskQueue* taskQueue[Task::NUM_PRIORITY];
        uint8_t threadIndex;
        thread::id threadId;
        thread poolThread;
        TaskMemoryAllocator allocator;
        mutex signal;
        condition_variable radio;
    };

public:

    BaseThreadPool();
    Task* DequeueTask();
    void Run(uint32_t threadNum);
    void Start(TaskGraph& taskGraph);
    void End();
    thread CreateThread(uint32_t threadNum);

public:

    static const uint32_t MAX_NUM_THREADS = 64;

    mutex key;
    condition_variable mailbox;
    atomic<bool> requestExit;
    uint8_t numThreads;

    Setup setup;
    ThreadData* threads[MAX_NUM_THREADS];

private:
    TaskGraph* taskGraph;
    TaskMemoryAllocator taskMemoryAllocator;
    thread_local static ThreadData* threadData;
};

template <class MemInterface>
BaseThreadPool<MemInterface>::BaseThreadPool() :
    requestExit(false),
    numThreads(0),
    taskGraph(nullptr)
{
    memset(threads, 0, sizeof(threads));
}

template <class MemInterface>
typename BaseThreadPool<MemInterface>::Task* BaseThreadPool<MemInterface>::DequeueTask()
{
    Task *nextTask = nullptr;
    for (uint32_t priority = 0; priority < Task::NUM_PRIORITY; priority++)
    {
        if (ThreadPool::threadData->taskQueue[priority]->pop_front(nextTask))
        {
            break;
        }
    }

    if (nextTask == nullptr)
    {
        //Try get from global task queue
        nextTask = taskGraph->DequeueTask();
    }
    return nextTask;
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Run(uint32_t threadNum)
{
    threadData = threads[threadNum];
    threadData->threadId = this_thread::get_id();

    ProfileTime scheduling(0ms), sleeping(0ms), working(0ms);
    auto exitRequested = false;

    //Signal Thread has started
    --setup.threadsNotStarted;
    setup.radio.notify_one();
    
    //Wakeup when all threads have started
    unique_lock<mutex> signal(threadData->signal);
    threadData->radio.wait(signal);

    cout << "Starting Thread " << uint32_t(threadData->threadIndex) << endl;

    while (!exitRequested)
    {
        //Steal Task
        Task* runTask = nullptr;
        {
            ProfileTimer profile(scheduling);

            //Try get a task
            runTask = DequeueTask();
        }

        if (runTask)
        {
            //Run Task
            ProfileTime taskTime(0ms);
            {
                ProfileTimer profile(taskTime);
                (*runTask)();
            }
            cout << "Task " << runTask->debug.taskName << " completed in " << chrono::duration_cast<chrono::milliseconds>(taskTime).count() << "ms" << endl;
            working += taskTime;

            //Donate More Tasks
            {
                ProfileTimer profile(scheduling);
                runTask->KickDependentTasks();
            }
        }
        else
        {
            //Go to sleep if there is no task to run
            ProfileTimer profile(sleeping);
            unique_lock<mutex> lock(key);
            mailbox.wait(lock);
        }

        //Check if we need to exit thread
        exitRequested = requestExit.load();
    };

    auto schedulingMS = chrono::duration_cast<chrono::milliseconds>(scheduling);
    auto sleepingMS = chrono::duration_cast<chrono::milliseconds>(sleeping);
    auto workingMS = chrono::duration_cast<chrono::milliseconds>(working);
    auto schedulingRatio = double(working.count() / (scheduling.count()==0 ? 1 : scheduling.count()));
    cout << "Thread " << uint32_t(threadData->threadIndex) << " Complete, Scheduling Overhead=" << schedulingMS.count() << "ms, Sleep Time=" << sleepingMS.count() << "ms, Work Time=" << workingMS.count() << "ms, Work/Schedule Ratio=" << fixed << setprecision(0) << schedulingRatio << endl;
}

template <class MemInterface>
thread BaseThreadPool<MemInterface>::CreateThread(uint32_t threadNum)
{
    return thread([&] { Run(threadNum); });
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::Start(TaskGraph& _taskGraph)
{
    taskGraph = &_taskGraph;
    numThreads = min(thread::hardware_concurrency(), MAX_NUM_THREADS);
    setup.threadsNotStarted.store(uint32_t(numThreads));
    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        ThreadData* thrData = new ThreadData();
        threads[threadIdx] = thrData;
        thrData->threadIndex = threadIdx;
        thrData->poolThread = CreateThread(threadIdx);
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
        threads[threadIdx]->radio.notify_one();
    }
}

template <class MemInterface>
void BaseThreadPool<MemInterface>::End()
{
    requestExit.store(true);
    mailbox.notify_all();
    for (uint32_t threadIdx = 0; threadIdx < numThreads; threadIdx++)
    {
        ThreadData *thrData = threads[threadIdx];
        thrData->poolThread.join();
        delete thrData;
    }
    memset(threads, 0, sizeof(threads));
}
