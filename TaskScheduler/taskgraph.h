#pragma once

#include "containers.h"

template <class MemInterface> class BaseTask;
template <class MemInterface> class BaseThreadPool;

template<class Task, class MemInterface>
struct BaseSubGraph : public MemInterface
{
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    TaskVector headTasks;
    TaskVector tailTasks;
    TaskVector taskList;

    //Frame Rate
    //Periodic Updates
};

template <class MemInterface>
class BaseTaskGraph : public MemInterface
{
public:
    static const uint32_t MAX_TASKS_PER_QUEUE = 200;

    typedef typename BaseTask<MemInterface>::Task Task;
    typedef basic_string<char, char_traits<char>, Allocator<char, MemInterface>> String;
    typedef BaseSubGraph<typename BaseTask<MemInterface>::Task, MemInterface> SubGraph;
    typedef LockFreeNodeDispenser<typename BaseTask<MemInterface>::Task*, MemInterface> TaskMemoryAllocator;
    typedef typename LockFreeQueue<MultiProducerMultiConsumer<typename BaseTask<MemInterface>::Task*, MemInterface, TaskMemoryAllocator>, typename BaseTask<MemInterface>::Task*, MemInterface, TaskMemoryAllocator*> TaskQueue;
    typedef unordered_map<String, Task*, hash<String>, equal_to<String>, Allocator<pair<const String, Task*>, MemInterface>> TaskNameToTaskMap;
    typedef vector<SubGraph*, Allocator<SubGraph*, MemInterface>> SubGraphVector;
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    typedef BaseThreadPool<MemInterface> ThreadPool;
    typedef Task* TaskList;

    struct Persistent
    {
        TaskVector headTasks;
        TaskVector tailTasks;
        SubGraphVector subGraphs;
    };

    struct Transient
    {
        Transient(TaskMemoryAllocator* allocator)
        {
            for (auto& queue : taskQueue)
            {
                queue = new TaskQueue(allocator);
            }
        }
        ~Transient()
        {
            for (auto& queue : taskQueue)
            {
                delete queue;
                queue = nullptr;
            }
        }
        TaskQueue* taskQueue[Task::NUM_PRIORITY];
    };

    struct Debug
    {
        TaskNameToTaskMap taskNameToTask;
        TaskVector taskList;
    };

public:

    BaseTaskGraph(ThreadPool& _pool);
    ~BaseTaskGraph();

    void Initialize(SubGraph* subGraph = nullptr);
    void Load(String fileName);
    void SetupTailKickers();
    void DepthFirstVisitor(Task* task, function<void(Task*)> nodePreRunFunctor, function<void(Task*)> nodePostRunFunctor, function<void(Task*)> tailRunFunctor);
    void Kick();

    void QueueTask(Task* task);
    Task* DequeueTask();

private:
    bool FindHead(TaskVector& headList);
    size_t Size(TaskList taskList) const;
    void SetupTask(Task* task, uint32_t taskFileField, String str);

private:
    TaskMemoryAllocator taskMemoryAllocator;
    ThreadPool& pool;

public:
    Persistent persistent;
    Transient transient;
    Debug debug;
};

template<class MemInterface>
BaseTaskGraph<MemInterface>::BaseTaskGraph(ThreadPool& _pool) :
    transient(&taskMemoryAllocator),
    pool(_pool)
{}

template<class MemInterface>
void BaseTaskGraph<MemInterface>::Initialize(SubGraph* graph)
{
    TaskVector *taskList;
    if (graph)
    {
        taskList = &(graph->taskList);
    }
    else
    {
        taskList = &(debug.taskList);
    }
    for (auto task : *taskList)
    {
        memset(&(task->transient), 0x0, sizeof(Task::Transient));
    }
    for (auto task : *taskList)
    {
        for (auto dependentTask : task->dependentTasks)
        {
            ++dependentTask->transient.startGate;
        }
    }
}

template<class MemInterface>
bool BaseTaskGraph<MemInterface>::FindHead(TaskVector& headList)
{
    auto foundAtLeastOneHead = false;
    for (auto task : debug.taskList)
    {
        uint64_t startGate = task->transient.startGate.load();
        if (startGate == 0)
        {
            headList.push_back(task);
            foundAtLeastOneHead = true;
        }
    }
    return foundAtLeastOneHead;
}

template<class MemInterface>
size_t BaseTaskGraph<MemInterface>::Size(TaskList taskList) const
{
    size_t count = 0;
    Task* itr = taskList;
    while (itr)
    {
        count++;
        itr = itr->transient.nextTask.load();
    }
    return count;
}

template<class MemInterface>
void BaseTaskGraph<MemInterface>::Load(String fileName)
{
    String line;
    ifstream taskFile(fileName.c_str());
    while (getline(taskFile, line))
    {
        typedef basic_istringstream<char, char_traits<char>, Allocator<char, MemInterface> > iStringstream;
        iStringstream iss(line);
        String token;
        auto newTask = new Task(*this);
        unsigned int taskFileField = 0;
        while (getline(iss, token, ','))
        {
            cout << token << std::endl;
            SetupTask(newTask, taskFileField, token);
            taskFileField++;
        }
        debug.taskNameToTask.insert({ newTask->debug.taskName, newTask });
        debug.taskList.push_back(newTask);
    }

    for (auto& task : debug.taskList)
    {
        for (auto& taskName : task->debug.dependentTaskNames)
        {
            auto dependentTask = debug.taskNameToTask.find(taskName);
            if (dependentTask != debug.taskNameToTask.end())
            {
                task->dependentTasks.push_back(dependentTask->second);
            }
            else
            {
                cout << "Cannot link" << task->debug.taskName << " to " << taskName << '\n';
            }
        }
    }

    //Initialize tasks' queue pointers and start gates
    Initialize();

    //Initialize head tasks
    auto bFound = FindHead(persistent.headTasks);
    //Check if we have at least one head
    assert(bFound);

    //Setup end nodes to start head nodes
    SetupTailKickers();

#if defined(DEBUG)
    //Check if there are more than one tail nodes per head node
    set<Task*> headNodesWithATailNode;
    for (auto tailTask : tailTasks)
    {
        for (auto kickTask : tailTask->kickTasks)
        {
            auto result = headNodesWithATailNode.insert(kickTask);
            assert(result.second);
        }
    }
#endif //DEBUG

    //Setup Subgraphs
    //Each subgraph has only 1 tail, so we get the heads in the tail to traverse all nodes to build a graph

    for (auto tailTask : persistent.tailTasks)
    {
        typedef set<Task*, less<Task*>, Allocator<Task*, MemInterface>> TaskSet;
        auto* subGraph = new SubGraph();
        subGraph->tailTasks.push_back(tailTask);
        TaskSet subGraphSet;
        for (auto kickTask : tailTask->kickTasks)
        {
            subGraph->headTasks.push_back(kickTask);
            DepthFirstVisitor(kickTask,
                bind(
                    [](Task* node, TaskSet *_subGraphSet, SubGraph* _subGraph)
            {
                _subGraphSet->insert(node);
                node->subGraph = _subGraph;
            },
                    _1, &subGraphSet, subGraph),
                [](Task* nodeTask) {},
                [](Task* nodeTask) {}
            );
        }
        copy(subGraphSet.begin(), subGraphSet.end(), back_inserter(subGraph->taskList));
        persistent.subGraphs.push_back(subGraph);
    }
}


template<class MemInterface>
void BaseTaskGraph<MemInterface>::SetupTailKickers()
{
    for (auto headTask : persistent.headTasks)
    {
        DepthFirstVisitor(headTask,
            [](Task* nodeTask)
        {

        },
            [](Task* nodeTask)
        {

        },
            bind(
                [](Task* tailTask, Task* _headTask, TaskVector *_tailTasks)
        {
            //Only add unique items
            auto result = find(begin(*_tailTasks), end(*_tailTasks), tailTask);
            if (result == end(*_tailTasks))
            {
                tailTask->kickTasks.push_back(_headTask);
                _tailTasks->push_back(tailTask);
            }
        },
                _1, headTask, &persistent.tailTasks)
            );
    }
}


template<class MemInterface>
void BaseTaskGraph<MemInterface>::DepthFirstVisitor(Task* task, function<void(Task*)> nodePreRunFunctor, function<void(Task*)> nodePostRunFunctor, function<void(Task*)> tailRunFunctor)
{
    nodePreRunFunctor(task);
    if (task->dependentTasks.size() == 0)
    {
        tailRunFunctor(task);
        return;
    }
    for (auto dependentTask : task->dependentTasks)
    {
        DepthFirstVisitor(dependentTask, nodePreRunFunctor, nodePostRunFunctor, tailRunFunctor);
    }
    nodePostRunFunctor(task);
}

template<class MemInterface>
BaseTaskGraph<MemInterface>::~BaseTaskGraph()
{
    for (auto &it : persistent.subGraphs)
    {
        delete it;
    }
    persistent.subGraphs.clear();
    for (auto &it : debug.taskList)
    {
        delete it;
    }
    debug.taskList.clear();
}

template<class MemInterface>
void BaseTaskGraph<MemInterface>::SetupTask(Task* task, uint32_t taskFileField, String str)
{
    enum TaskFileField
    {
        TaskName,
        TaskPriority,
        DependentTask1,
        DependentTask2,
        DependentTask3,
        DependentTask4,
        DependentTask5,
    };

    switch (taskFileField)
    {
    case TaskName:
        task->debug.taskName = str;
        break;
    case TaskPriority:
    {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        for (auto i = 0; i < Task::NUM_PRIORITY; i++)
        {
            if (str.compare(task->debug.PriorityToString(Task::Priority(i))) == 0)
            {
                task->taskPriority = Task::Priority(i);
            }
        }
        break;
    }
    default:
        task->debug.dependentTaskNames.push_back(str);
        break;
    }
}

template<class MemInterface>
void BaseTaskGraph<MemInterface>::Kick()
{
    Initialize();
    for (auto headTask : persistent.headTasks)
    {
        QueueTask(headTask);
    }
}

template<class MemInterface>
void BaseTaskGraph<MemInterface>::QueueTask(Task* task)
{
    bool result = false;
    uint32_t priority = task->taskPriority;
    do {
    } while (!transient.taskQueue[priority]->push_back(task) && ++priority < Task::NUM_PRIORITY);
    assert(priority < Task::NUM_PRIORITY);

    pool.mailbox.notify_one();
}

template<class MemInterface>
typename BaseTask<MemInterface>::Task* BaseTaskGraph<MemInterface>::DequeueTask()
{
    Task *nextTask = nullptr;
    for (uint32_t priority = 0; priority < Task::NUM_PRIORITY; priority++)
    {
        if (transient.taskQueue[priority]->pop_front(nextTask))
        {
            break;
        }
    }
    return nextTask;
}

