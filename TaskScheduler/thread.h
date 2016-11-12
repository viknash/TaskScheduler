#pragma once

#include "profile.h"
#include "containers.h"

template <class MemInterface> class BaseTask;
template <class MemInterface> class BaseTaskGraph;
template <class MemInterface> class BaseThreadPool;

template <class MemInterface>
struct BaseThread : public MemInterface
{
    typedef typename BaseTaskGraph<MemInterface> TaskGraph;
    typedef typename TaskGraph::Task Task;
    typedef typename TaskGraph::TaskQueue TaskQueue;
    typedef typename BaseThread<MemInterface> Thread;
    typedef typename BaseThreadPool<MemInterface> ThreadPool;
    typedef typename TaskGraph::TaskMemoryAllocator TaskMemoryAllocator;

    BaseThread(uint8_t _threadIndex, ThreadPool* _pool);
    ~BaseThread();

    static Thread* CreateThread(ThreadPool* pool);

    void Sleep();
    void Wakeup();
    void Join();

    TaskQueue*  taskQueue[Task::NUM_PRIORITY];
    uint8_t     threadIndex;
    thread::id  threadId;
    thread      taskThread;
    TaskMemoryAllocator allocator;

    friend class thread;

private:
    void Init();
    void Run();
    Task* GetTask();

    ThreadPool& pool;
    mutex signal;
    condition_variable radio;
};

template <class MemInterface>
BaseThread<MemInterface>::BaseThread(uint8_t _threadIndex, ThreadPool* _pool) :
    threadIndex(_threadIndex),
    pool(*_pool)
{
    for (auto& queue : taskQueue)
    {
        queue = new TaskQueue(&allocator);
    }

    taskThread = thread([&] {
        Init();
        Run();
    });
}

template <class MemInterface>
BaseThread<MemInterface>::~BaseThread()
{
    for (auto& queue : taskQueue)
    {
        delete queue;
        queue = nullptr;
    }
}

template <class MemInterface>
BaseThread<MemInterface>* BaseThread<MemInterface>::CreateThread(ThreadPool* pool)
{
    static uint32_t nextThreadNum = 0;
    return new Thread(nextThreadNum++, pool);
}

template <class MemInterface>
void BaseThread<MemInterface>::Init()
{
    threadId = this_thread::get_id();
    pool.currentThread = this;

    //Signal Thread has started
    --pool.setup.threadsNotStarted;
    pool.setup.radio.notify_one();

    //Wakeup when all threads have started
    unique_lock<mutex> signalLock(signal);
    radio.wait(signalLock);
}

template <class MemInterface>
void BaseThread<MemInterface>::Sleep()
{
    unique_lock<mutex> signalLock(signal);
    radio.wait(signalLock);
}

template <class MemInterface>
void BaseThread<MemInterface>::Wakeup()
{
    radio.notify_one();
}

template <class MemInterface>
void BaseThread<MemInterface>::Join()
{
    taskThread.join();
}

template <class MemInterface>
void BaseThread<MemInterface>::Run()
{
    auto exitRequested = false;
    ProfileTime scheduling(0ms), sleeping(0ms), working(0ms);

    cout << "Starting Thread " << uint32_t(threadIndex) << endl;

    while (!exitRequested)
    {
        //Steal Task
        Task* runTask = Instrument<Task*, Thread, Task*(Thread::*)()>(scheduling, this, &Thread::GetTask);

        if (runTask)
        {
            //Run Task
            ProfileTime taskTime(0ms);
            Instrument<void, Task, void(Task::*)()>(taskTime, runTask, &Task::operator());
            cout << "Thread(" << uint32_t(threadIndex) << "), Task " << runTask->debug.taskName << "(" << chrono::duration_cast<chrono::milliseconds>(taskTime).count() << "ms)" << endl;
            working += taskTime;

            //Donate More Tasks
            Instrument<void, Task, void(Task::*)()>(scheduling, runTask, &Task::KickDependentTasks);
        }
        else
        {
            //Go to sleep if there is no task to run
            Instrument<void, Thread, void(Thread::*)()>(sleeping, this, &Thread::Sleep);
        }

        //Check if we need to exit thread
        exitRequested = pool.setup.requestExit.load();
    };

    auto schedulingMS = chrono::duration_cast<chrono::milliseconds>(scheduling);
    auto sleepingMS = chrono::duration_cast<chrono::milliseconds>(sleeping);
    auto workingMS = chrono::duration_cast<chrono::milliseconds>(working);
    auto schedulingRatio = double(working.count() / (scheduling.count() == 0 ? 1 : scheduling.count()));
    cout << "Thread " << uint32_t(threadIndex) << " Complete, Scheduling Overhead=" << schedulingMS.count() << "ms, Sleep Time=" << sleepingMS.count() << "ms, Work Time=" << workingMS.count() << "ms, Work/Schedule Ratio=" << fixed << setprecision(0) << schedulingRatio << endl;
}

template <class MemInterface>
typename BaseThread<MemInterface>::Task* BaseThread<MemInterface>::GetTask()
{
    Task *nextTask = nullptr;
    for (uint32_t priority = 0; priority < Task::NUM_PRIORITY; priority++)
    {
        //Try to get a task from the thread queue
        if (taskQueue[priority]->pop_front(nextTask))
        {
            break;
        }

        //Try to get a task from the global queue
        if (nextTask = pool.taskGraph->DequeueTask(priority))
        {
            pool.queueRank[priority][threadIndex].fetch_add(nextTask->persistent.rank);
            break;
        }
    }

    return nextTask;
}