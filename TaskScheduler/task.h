#pragma once


template <class MemInterface> class BaseTaskGraph;
template <class MemInterface> class BaseThreadPool;
template<class Task, class MemInterface> struct BaseSubGraph;

template <class MemInterface>
class BaseTask
{
public:
    typedef BaseTask<MemInterface> Task;
    typedef BaseTaskGraph<MemInterface> TaskGraph;
    typedef BaseSubGraph<Task, MemInterface> SubGraph;
    typedef vector<string, Allocator<string, MemInterface>> StringVector;
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;

    enum Priority
    {
        REALTIME,
        HIGH,
        NORMAL,
        LOW,
        NUM_PRIORITY
    };

    struct Debug
    {
        string taskName;
        StringVector dependentTaskNames;

        const char* PriorityToString(Priority priority) const;
    };

    struct Transient
    {
        atomic_int64_t  startGate;
        atomic<Task*>   nextTask;
    };

    Priority taskPriority;
    TaskVector dependentTasks;
    SubGraph* subGraph;
    function <void()> runFunctor;
    Debug debug;
    Transient transient;

    TaskVector kickTasks;

   BaseTask(BaseTaskGraph<MemInterface>& _taskGraph);

    void KickDependentTasks();
    void operator()();
private:
    BaseTaskGraph<MemInterface>& taskGraph;
};

//typedef BaseTask<DefaultMemInterface>* TaskList;

//typedef BaseTask<DefaultMemInterface> Task;

template <class MemInterface>
BaseTask<MemInterface>::BaseTask(BaseTaskGraph<MemInterface>& _taskGraph) :
    taskPriority(NORMAL),
    taskGraph(_taskGraph)
{

}

template <class MemInterface>
const char* BaseTask<MemInterface>::Debug::PriorityToString(Priority priority) const
{
    static const char* PriorityToString[] =
    {
        "REALTIME",
        "HIGH",
        "NORMAL",
        "LOW"
    };

    return PriorityToString[uint32_t(priority)];
}

template <class MemInterface>
void BaseTask<MemInterface>::KickDependentTasks()
{
    //Queue dependent tasks only when their start gates are 0
    //i.e. all parent tasks have been executed
    for (auto dependentTask : dependentTasks)
    {
        if (--dependentTask->transient.startGate == 0)
        {
            taskGraph.QueueTask(dependentTask);
        }
    }

    //Only Tail Task Nodes should have kick tasks
    //Kick tasks are Head Tasks for the next frame
    bool initializedSubGraph = false;
    for (auto kickTask : kickTasks)
    {
        if (!initializedSubGraph)
        {
            taskGraph.Initialize(kickTask->subGraph);
            initializedSubGraph = true;
        }
        uint64_t startGate = kickTask->transient.startGate.load();
        assert(startGate == 0);
        taskGraph.QueueTask(kickTask);
    }
}

template <class MemInterface>
void BaseTask<MemInterface>::operator()()
{
    runFunctor();
}