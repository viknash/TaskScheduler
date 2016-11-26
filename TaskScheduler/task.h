#pragma once

#include "meta.h"
#include "memory.h"

template <class MemInterface>
class BaseTaskGraph;
template <class MemInterface>
class BaseThreadPool;
template <class MemInterface>
struct BaseThread;
template <class Task, class MemInterface>
struct BaseSubGraph;

template <class MemInterface>
class BaseTask : public MemInterface {
public:
    typedef BaseTask<MemInterface> Task;
    typedef BaseThread<MemInterface> Thread;
    typedef BaseTaskGraph<MemInterface> TaskGraph;
    typedef BaseSubGraph<Task, MemInterface> SubGraph;
    typedef basic_string<char, char_traits<char>, Allocator<char, MemInterface>> String;
    typedef vector<String, Allocator<String, MemInterface>> StringVector;
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    typedef BaseThreadPool<MemInterface> ThreadPool;
    typedef function<void()> Function;
    typedef typename int64_t Rank;

    enum Priority {
        REALTIME,
        HIGH,
        NORMAL,
        LOW,
        NUM_PRIORITY
    };

    struct Debug {
        const char* PriorityToString(Priority priority) const;

        String taskName;
        StringVector dependentTaskNames;
    };

    struct Transient {
        atomic_int64_t startGate;
    };

    struct Persistent {
        Persistent();

        Priority taskPriority;
        TaskVector parentTasks;
        TaskVector dependentTasks;
        TaskVector kickTasks;
        Function runFunctor;
        SubGraph* subGraph;
        Rank rank;
        int64_t threadAffinity;
    };

    void SetThreadAffinity(uint64_t mask);
    void SetThreadExclusion(uint64_t mask);
    BaseTask(TaskGraph& _taskGraph);
    void KickDependentTasks();
    void operator()();

    Debug debug;
    Transient transient;
    Persistent persistent;
    TaskGraph& taskGraph;
};

template <class MemInterface>
const char* BaseTask<MemInterface>::Debug::PriorityToString(Priority priority) const
{
    static const char* PriorityToString[] = {
        "REALTIME",
        "HIGH",
        "NORMAL",
        "LOW"
    };

    return PriorityToString[uint32_t(priority)];
}

template <class MemInterface>
BaseTask<MemInterface>::Persistent::Persistent()
    : taskPriority(NORMAL)
    , subGraph(nullptr)
    , rank(0)
    , threadAffinity(0)
{
}

template <class MemInterface>
void BaseTask<MemInterface>::operator()()
{
    persistent.runFunctor();
}

template <class MemInterface>
void BaseTask<MemInterface>::SetThreadAffinity(uint64_t mask)
{
    taskGraph.SetTaskThreadAffinity(this, mask);
}

template <class MemInterface>
void BaseTask<MemInterface>::SetThreadExclusion(uint64_t mask)
{
    taskGraph.SetTaskThreadExclusion(this, mask);
}

template <class MemInterface>
BaseTask<MemInterface>::BaseTask(TaskGraph& _taskGraph)
    : taskGraph(_taskGraph)
{
}

template <class MemInterface>
void BaseTask<MemInterface>::KickDependentTasks()
{
    //Reduce queue rank of queue that the current task is running on
    Priority currentTaskPriority = persistent.taskPriority;
    taskGraph.pool.queueRank[persistent.taskPriority][taskGraph.pool.currentThread->threadIndex].fetch_sub(persistent.rank);

    //Queue dependent tasks only when their start gates are 0
    //i.e. all parent tasks have been executed

    //If we are scheduling many tasks at once search for the next best ranked queue, starting from just after the queue that was just scheduled
    reduce_starvation(new_search_index) uint32_t bestSearchIndex = taskGraph.pool.currentThread->threadIndex;

    for (auto dependentTask : persistent.dependentTasks) {
        if (--dependentTask->transient.startGate == 0) {
            //Find lowest ranking queue, aka best queue and increment its rank with dependent task rank
            uint32_t currentThreadIndex = 0;
            Thread* bestThread = nullptr;
            Rank bestRank = numeric_limits<Rank>::max();
            do {
                bestThread = nullptr;
                bestRank = numeric_limits<Rank>::max();
                reduce_starvation(new_search_index) currentThreadIndex = bestSearchIndex;
                while ((currentThreadIndex = (currentThreadIndex + 1) % taskGraph.pool.numThreads) != bestSearchIndex) {
                    if (!(dependentTask->persistent.threadAffinity & 1ull << currentThreadIndex))
                        continue; //Skip threads the task should not run on

                    int64_t currentThreadRank = taskGraph.pool.queueRank[dependentTask->persistent.taskPriority][currentThreadIndex].load();
                    if (currentThreadRank < bestRank) {
                        bestRank = currentThreadRank;
                        bestThread = taskGraph.pool.threads[currentThreadIndex];
                    }
                }
            } while (!taskGraph.pool.queueRank[dependentTask->persistent.taskPriority][bestThread->threadIndex].compare_exchange_weak(bestRank, bestRank + dependentTask->persistent.rank));

            //Push task into the best queue
            uint32_t dependentTaskPriority = dependentTask->persistent.taskPriority;
            do {
            } while (!bestThread->taskQueue[dependentTaskPriority]->push_back(dependentTask) && ++dependentTaskPriority < Task::NUM_PRIORITY);
            assert(dependentTaskPriority < Task::NUM_PRIORITY);

            //Wakeup thread if its sleeping
            bestThread->Wakeup();

            reduce_starvation(new_search_index) bestSearchIndex = bestThread->threadIndex;
        }
    }

    //Stop kicking tasks when a request to pause has been received
    //If all tail kickers have paused, then request the threads to stop
    if (persistent.kickTasks.size() && taskGraph.pool.setup.requestExit == ThreadPool::RequestPause) {
        --taskGraph.pool.setup.threadSync;
        if (!taskGraph.pool.setup.threadSync) {
            taskGraph.pool.setup.requestExit.store(ThreadPool::RequestStop);
            taskGraph.pool.Wakeup();
        }
        return;
    }

    //Only Tail Task Nodes should have kick tasks
    //Kick tasks are Head Tasks for the next frame
    bool initializedSubGraph = false;
    for (auto kickTask : persistent.kickTasks) {
        if (!initializedSubGraph) {
            taskGraph.Initialize(kickTask->persistent.subGraph);
            initializedSubGraph = true;
        }
        uint64_t startGate = kickTask->transient.startGate.load();
        assert(startGate == 0);
        taskGraph.QueueTask(kickTask);
    }
}