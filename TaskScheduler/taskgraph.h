#pragma once

#include "containers.h"

template <class MemInterface>
class BaseTask;
template <class MemInterface>
class BaseThreadPool;

template <class Task, class MemInterface>
struct BaseSubGraph : public MemInterface {
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    TaskVector headTasks;
    TaskVector tailTasks;
    TaskVector taskList;

    // Frame Rate
    // Periodic Updates
};

template <class MemInterface>
class BaseTaskGraph : public MemInterface {
public:
    static const uint32_t MAX_TASKS_PER_QUEUE = 200;

    typedef typename BaseTask<MemInterface>::Task Task;
    typedef basic_string<char, char_traits<char>, Allocator<char, MemInterface>>
        String;
    typedef BaseSubGraph<typename BaseTask<MemInterface>::Task, MemInterface>
        SubGraph;
    typedef LockFreeNodeDispenser<typename BaseTask<MemInterface>::Task*,
        MemInterface>
        TaskMemoryAllocator;
    typedef typename LockFreeQueue<MultiProducerMultiConsumer<typename BaseTask<MemInterface>::Task*,
                                       MemInterface, TaskMemoryAllocator>,
        typename BaseTask<MemInterface>::Task*, MemInterface,
        TaskMemoryAllocator*>
        TaskQueue;
    typedef unordered_map<String, Task*, hash<String>, equal_to<String>,
        Allocator<pair<const String, Task*>, MemInterface>>
        TaskNameToTaskMap;
    typedef vector<SubGraph*, Allocator<SubGraph*, MemInterface>> SubGraphVector;
    typedef vector<Task*, Allocator<Task*, MemInterface>> TaskVector;
    typedef BaseThreadPool<MemInterface> ThreadPool;
    typedef Task* TaskList;

    struct Persistent {
        TaskVector headTasks;
        TaskVector tailTasks;
        SubGraphVector subGraphs;
    };

    struct Transient {
        Transient(TaskMemoryAllocator* allocator)
        {
            for (auto& queue : taskQueue) {
                queue = new TaskQueue(allocator);
            }
        }
        ~Transient()
        {
            for (auto& queue : taskQueue) {
                delete queue;
                queue = nullptr;
            }
        }
        TaskQueue* taskQueue[Task::NUM_PRIORITY];
    };

    struct Debug {
        TaskNameToTaskMap taskNameToTask;
        TaskVector taskList;
    };

public:
    BaseTaskGraph(ThreadPool& _pool);
    ~BaseTaskGraph();

    void Initialize(SubGraph* subGraph = nullptr);
    void Load(String fileName);
    void SetTaskThreadAffinity(Task* task, uint64_t mask);
    void SetTaskThreadExclusion(Task* task, uint64_t mask);
    void SetupTailKickers();
    void DepthFirstVisitor(Task* task,
        function<void(Task*, void*&)> preOrderFunctor,
        function<void(Task*, void*&)> inOrderFunctor,
        function<void(Task*, void*&)> postOrderFunctor,
        function<void(Task*, void*&)> tailFunctor, void* param,
        bool bottomUp = false);
    void Kick();

    void QueueTask(Task* task, uint8_t numThreadsToWakeup = 1);
    Task* DequeueTask(uint32_t priority);
    bool IsTaskAvailable();

private:
    bool FindHead(TaskVector& headList);
    size_t Size(TaskList taskList) const;
    void SetupTask(Task* task, uint32_t taskFileField, String str);
    TaskMemoryAllocator taskMemoryAllocator;

public:
    Persistent persistent;
    Transient transient;
    Debug debug;
    ThreadPool& pool;
};

template <class MemInterface>
BaseTaskGraph<MemInterface>::BaseTaskGraph(ThreadPool& _pool)
    : transient(&taskMemoryAllocator)
    , pool(_pool)
{
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::Initialize(SubGraph* graph)
{
    TaskVector* taskList;
    if (graph) {
        taskList = &(graph->taskList);
    } else {
        taskList = &(debug.taskList);
    }
    for (auto task : *taskList) {
        memset(&(task->transient), 0x0, sizeof(Task::Transient));
    }
    for (auto task : *taskList) {
        for (auto dependentTask : task->persistent.dependentTasks) {
            ++dependentTask->transient.startGate;
        }
    }
}

template <class MemInterface>
bool BaseTaskGraph<MemInterface>::FindHead(TaskVector& headList)
{
    auto foundAtLeastOneHead = false;
    for (auto task : debug.taskList) {
        uint64_t startGate = task->transient.startGate.load();
        if (startGate == 0) {
            headList.push_back(task);
            foundAtLeastOneHead = true;
        }
    }
    return foundAtLeastOneHead;
}

template <class MemInterface>
size_t BaseTaskGraph<MemInterface>::Size(TaskList taskList) const
{
    size_t count = 0;
    Task* itr = taskList;
    while (itr) {
        count++;
        itr = itr->transient.nextTask.load();
    }
    return count;
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::Load(String fileName)
{
    String line;
    ifstream taskFile(fileName.c_str());
    while (getline(taskFile, line)) {
        typedef basic_istringstream<char, char_traits<char>,
            Allocator<char, MemInterface>>
            iStringstream;
        iStringstream iss(line);
        String token;
        auto newTask = new Task(*this);
        unsigned int taskFileField = 0;
        while (getline(iss, token, ',')) {
            cout << token << std::endl;
            SetupTask(newTask, taskFileField, token);
            taskFileField++;
        }
        debug.taskNameToTask.insert({ newTask->debug.taskName, newTask });
        debug.taskList.push_back(newTask);
    }

    for (auto& task : debug.taskList) {
        for (auto& taskName : task->debug.dependentTaskNames) {
            auto dependentTask = debug.taskNameToTask.find(taskName);
            if (dependentTask != debug.taskNameToTask.end()) {
                task->persistent.dependentTasks.push_back(dependentTask->second);
                dependentTask->second->persistent.parentTasks.push_back(task);
            } else {
                cout << "Cannot link" << task->debug.taskName << " to " << taskName
                     << '\n';
            }
        }
    }

    // Initialize tasks' queue pointers and start gates
    Initialize();

    // Initialize head tasks
    auto bFound = FindHead(persistent.headTasks);
    // Check if we have at least one head
    assert(bFound);

    // Setup end nodes to start head nodes
    SetupTailKickers();

#if defined(DEBUG)
    // Check if there are more than one tail nodes per head node
    set<Task*> headNodesWithATailNode;
    for (auto tailTask : tailTasks) {
        for (auto kickTask : tailTask->kickTasks) {
            auto result = headNodesWithATailNode.insert(kickTask);
            assert(result.second);
        }
    }
#endif // DEBUG

    typedef set<Task*, less<Task*>, Allocator<Task*, MemInterface>> TaskSet;

    // Setup Subgraphs
    // Each subgraph has only 1 tail, so we get the heads in the tail to traverse
    // all nodes to build a graph
    for (auto tailTask : persistent.tailTasks) {
        auto* subGraph = new SubGraph();
        subGraph->tailTasks.push_back(tailTask);
        TaskSet subGraphSet;
        for (auto kickTask : tailTask->persistent.kickTasks) {
            subGraph->headTasks.push_back(kickTask);
            void* param = nullptr;
            DepthFirstVisitor(kickTask,
                bind(
                    [](Task* node, void*& param, TaskSet* _subGraphSet,
                        SubGraph* _subGraph) {
                        _subGraphSet->insert(node);
                        node->persistent.subGraph = _subGraph;
                    },
                    _1, _2, &subGraphSet, subGraph),
                nullptr, nullptr, nullptr, param);
        }
        copy(subGraphSet.begin(), subGraphSet.end(),
            back_inserter(subGraph->taskList));
        persistent.subGraphs.push_back(subGraph);
    }

    TaskSet rankedTasks;
    function<void(Task*, void*&)> rankingFunc = [](Task* nodeTask, void*& param) {
        param = (void*)1;
        nodeTask->persistent.rank += (Task::Rank)(param);
        cout << nodeTask->debug.taskName
             << " - Rank :" << int32_t(nodeTask->persistent.rank) << endl;
    };

    // Rank Nodes
    for (auto subGraph : persistent.subGraphs) {
        for (auto bottomHeadTask : subGraph->tailTasks) {
            // bottomHeadTask->persistent.rank =
            // (Task::Rank)bottomHeadTask->persistent.dependentTasks.size();
            void* param = nullptr; // (void*)bottomHeadTask->persistent.rank;
            DepthFirstVisitor(bottomHeadTask, rankingFunc, nullptr, nullptr, nullptr,
                param, true);
        }
    }

    struct rank_sorter {
        static bool compare(Task*& a, Task*& b)
        {
            return (a->persistent.rank < b->persistent.rank ? true : false);
        }
    };

    // Sort dependent tasks for each task based on rank
    for (auto& task : debug.taskList) {
        sort(task->persistent.dependentTasks.begin(),
            task->persistent.dependentTasks.end(), rank_sorter::compare);
    }

    // Correct thread affinity masks of all tasks
    for (auto headTask : persistent.headTasks) {
        void* param = nullptr;
        DepthFirstVisitor(headTask,
            [&](Task* task, void*& param) {
                SetTaskThreadAffinity(task,
                    task->persistent.threadAffinity);
            },
            nullptr, nullptr, nullptr, param);
    }
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::SetTaskThreadAffinity(Task* task,
    uint64_t mask)
{
    task->persistent.threadAffinity = 0;
    uint64_t validThreadMask = 1ull << pool.numThreads;
    validThreadMask = validThreadMask - 1;
    while (mask) {
        task->persistent.threadAffinity |= mask & validThreadMask;
        mask = mask >> pool.numThreads;
    }
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::SetTaskThreadExclusion(Task* task,
    uint64_t mask)
{
    mask = ~mask;
    uint64_t validThreadMask = 1ull << pool.numThreads;
    validThreadMask = validThreadMask - 1;
    mask = mask & validThreadMask;
    SetTaskThreadAffinity(task, mask);
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::SetupTailKickers()
{
    for (auto headTask : persistent.headTasks) {
        void* param = nullptr;
        DepthFirstVisitor(
            headTask, nullptr, nullptr, nullptr,
            bind(
                [](Task* tailTask, void*& param, Task* _headTask,
                    TaskVector* _tailTasks) {
                    // Only add unique items
                    auto result = find(begin(*_tailTasks), end(*_tailTasks), tailTask);
                    if (result == end(*_tailTasks)) {
                        tailTask->persistent.kickTasks.push_back(_headTask);
                        _tailTasks->push_back(tailTask);
                    }
                },
                _1, _2, headTask, &persistent.tailTasks),
            param);
    }
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::DepthFirstVisitor(
    Task* task, function<void(Task*, void*&)> preOrderFunctor,
    function<void(Task*, void*&)> inOrderFunctor,
    function<void(Task*, void*&)> postOrderFunctor,
    function<void(Task*, void*&)> tailFunctor, void* param, bool bottomup)
{
    if (preOrderFunctor)
        preOrderFunctor(task, param);
    if (bottomup) {
        if (task->persistent.parentTasks.size() == 0) {
            if (tailFunctor)
                tailFunctor(task, param);
            return;
        }
        for (auto parentTask : task->persistent.parentTasks) {
            DepthFirstVisitor(parentTask, preOrderFunctor, inOrderFunctor,
                postOrderFunctor, tailFunctor, param, bottomup);
            if (inOrderFunctor)
                inOrderFunctor(task, param);
        }
    } else {
        if (task->persistent.dependentTasks.size() == 0) {
            if (tailFunctor)
                tailFunctor(task, param);
            return;
        }
        for (auto dependentTask : task->persistent.dependentTasks) {
            DepthFirstVisitor(dependentTask, preOrderFunctor, inOrderFunctor,
                postOrderFunctor, tailFunctor, param, bottomup);
            if (inOrderFunctor)
                inOrderFunctor(task, param);
        }
    }
    if (postOrderFunctor)
        postOrderFunctor(task, param);
}

template <class MemInterface>
BaseTaskGraph<MemInterface>::~BaseTaskGraph()
{
    for (auto& it : persistent.subGraphs) {
        delete it;
    }
    persistent.subGraphs.clear();
    for (auto& it : debug.taskList) {
        delete it;
    }
    debug.taskList.clear();
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::SetupTask(Task* task, uint32_t taskFileField,
    String str)
{
    enum TaskFileField {
        TaskName,
        TaskPriority,
        DependentTask1,
        DependentTask2,
        DependentTask3,
        DependentTask4,
        DependentTask5,
    };

    switch (taskFileField) {
    case TaskName:
        task->debug.taskName = str;
        break;
    case TaskPriority: {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        for (auto i = 0; i < Task::NUM_PRIORITY; i++) {
            if (str.compare(task->debug.PriorityToString(Task::Priority(i))) == 0) {
                task->persistent.taskPriority = Task::Priority(i);
            }
        }
        break;
    }
    default:
        task->debug.dependentTaskNames.push_back(str);
        break;
    }
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::Kick()
{
    Initialize();
    for (auto headTask : persistent.headTasks) {
        QueueTask(headTask);
    }
}

template <class MemInterface>
void BaseTaskGraph<MemInterface>::QueueTask(Task* task,
    uint8_t numThreadsToWakeup)
{
    bool result = false;
    uint32_t priority = task->persistent.taskPriority;
    do {
    } while (!transient.taskQueue[priority]->push_back(task) && ++priority < Task::NUM_PRIORITY);
    assert(priority < Task::NUM_PRIORITY);

    pool.Wakeup(numThreadsToWakeup);
}

template <class MemInterface>
typename BaseTask<MemInterface>::Task* BaseTaskGraph<MemInterface>::DequeueTask(
    uint32_t priority)
{
    Task* nextTask = nullptr;
    transient.taskQueue[priority]->pop_front(nextTask);
    return nextTask;
}

template <class MemInterface>
bool BaseTaskGraph<MemInterface>::IsTaskAvailable()
{
    for (auto queue : transient.taskQueue) {
        if (!queue->empty()) {
            return true;
        }
    }
    return false;
}