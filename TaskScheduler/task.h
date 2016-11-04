#pragma once


template <class MemInterface> class BaseTaskGraph;
template <class MemInterface> class BaseThreadPool;
template<class Task, class MemInterface> struct BaseSubGraph;

template <class MemInterface>
class BaseTask : public MemInterface
{
public:
    typedef BaseTask<MemInterface> Task;
    typedef BaseTaskGraph<MemInterface> TaskGraph;
    typedef BaseSubGraph<Task, MemInterface> SubGraph;
    typedef basic_string<char, char_traits<char>, Allocator<char, MemInterface>> String;
    typedef vector<String, Allocator<String, MemInterface>> StringVector;
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    typedef function <void()> Function;
    typedef int64_t Rank;

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
        const char* PriorityToString(Priority priority) const
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

        String taskName;
        StringVector dependentTaskNames;
    };

    struct Transient
    {
        atomic_int64_t  startGate;
    };

    struct Persistent
    {
        Persistent() :
            taskPriority(NORMAL),
            subGraph(nullptr)
        {}

        Priority taskPriority;
        TaskVector parentTasks;
        TaskVector dependentTasks;
        TaskVector kickTasks;
        Function runFunctor;
        SubGraph* subGraph;
        Rank rank;
    };

    BaseTask(TaskGraph& _taskGraph) :
        taskGraph(_taskGraph)
    {

    }

    void KickDependentTasks()
    {
        //Queue dependent tasks only when their start gates are 0
        //i.e. all parent tasks have been executed
        for (auto dependentTask : persistent.dependentTasks)
        {
            if (--dependentTask->transient.startGate == 0)
            {
                taskGraph.QueueTask(dependentTask);
            }
        }

        //Only Tail Task Nodes should have kick tasks
        //Kick tasks are Head Tasks for the next frame
        bool initializedSubGraph = false;
        for (auto kickTask : persistent.kickTasks)
        {
            if (!initializedSubGraph)
            {
                taskGraph.Initialize(kickTask->persistent.subGraph);
                initializedSubGraph = true;
            }
            uint64_t startGate = kickTask->transient.startGate.load();
            assert(startGate == 0);
            taskGraph.QueueTask(kickTask);
        }
    }

    void operator()()
    {
        persistent.runFunctor();
    }

    Debug debug;
    Transient transient;
    Persistent persistent;

private:
    TaskGraph& taskGraph;
};
