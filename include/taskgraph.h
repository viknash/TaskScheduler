#pragma once

#include <algorithm>
#include <cinttypes>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <unordered_map>

#include "containers.h"

namespace task_scheduler
{

    template < class TMemInterface > class base_task;
    template < class TMemInterface > class base_thread_pool;

    template < class task_type, class TMemInterface > struct base_sub_graph : public TMemInterface
    {
        typedef std::vector< task_type *, stl_allocator< task_type *, TMemInterface > > task_vector;
        task_vector head_tasks;
        task_vector tail_tasks;
        task_vector task_list;

        // Frame Rate
        // Periodic Updates
    };

    template < class TMemInterface > class base_task_graph : public TMemInterface
    {
      public:
        typedef base_task< TMemInterface > task_type;
        typedef std::basic_string< char, std::char_traits< char >, stl_allocator< char, TMemInterface > > string_type;
        typedef base_sub_graph< task_type, TMemInterface > sub_graph_type;
        typedef lock_free_node_dispenser< task_type *, TMemInterface > task_memory_allocator_type;
        typedef lock_free_queue<
            multi_producer_multi_consumer< task_type *, TMemInterface, task_memory_allocator_type >,
            typename base_task< TMemInterface >::task_type *, TMemInterface, task_memory_allocator_type * >
            task_queue_type;
        typedef std::unordered_map< string_type, task_type *, std::hash< string_type >, std::equal_to< string_type >,
                                    stl_allocator< std::pair< const string_type, task_type * >, TMemInterface > >
            task_name_to_task_map;
        typedef std::vector< sub_graph_type *, stl_allocator< sub_graph_type *, TMemInterface > > sub_graph_vector;
        typedef std::vector< task_type *, stl_allocator< task_type *, TMemInterface > > task_vector;
        typedef base_thread_pool< TMemInterface > thread_pool;
        typedef task_type *task_list;
        typedef std::function< void(task_type *, void *&) > traversal_function_type;

        struct persistent_container
        {
            task_vector head_tasks;
            task_vector tail_tasks;
            sub_graph_vector sub_graphs;
        };

        struct transient_container
        {
            transient_container(task_memory_allocator_type *allocator)
            {
                for (auto &queue : task_queue)
                {
                    queue = new task_queue_type(allocator);
                }
            }
            ~transient_container()
            {
                for (auto &queue : task_queue)
                {
                    delete queue;
                    queue = nullptr;
                }
            }
            task_queue_type *task_queue[task_type::num_priority];
        };

        struct debug_container
        {
            task_name_to_task_map task_name_to_task;
            task_vector task_list;
        };

      public:
        base_task_graph(thread_pool &_pool);
        ~base_task_graph();

        void setup(sub_graph_type *_sub_graph = nullptr);
        void load(string_type _file_name);
        void initialize();
        void set_task_thread_affinity(task_type *_task, uint64_t _mask);
        void set_task_thread_exclusion(task_type *_task, uint64_t _mask);
        void set_num_workers(task_type *_task, thread_num_t _num_workers);
        void set_percentage_of_workers(task_type *_task, float _percentage_workers);
        void setup_tail_kickers();
        void depth_first_visitor(task_type *_task, traversal_function_type _preorder_functor,
                                 traversal_function_type _inorder_functor, traversal_function_type _post_order_functor,
                                 traversal_function_type _tail_functor, void *_param, bool _bottom_up = false);
        void kick();

        void queue_task(task_type *_task, thread_num_t _num_threads_to_wake_up = 1);
        task_type *dequeue_task(uint32_t _priority);
        bool is_task_available();
        bool link_task(task_type *_parent_task, task_type *_dependent_task);

      private:
        bool find_head(task_vector &_head_list);
        size_t size(task_list _task_list) const;
        task_memory_allocator_type task_memory_allocator;

      public:
        persistent_container persistent;
        transient_container transient;
        debug_container debug;
        thread_pool &pool;
    };

    template < class TMemInterface >
    base_task_graph< TMemInterface >::base_task_graph(thread_pool &_pool)
        : transient(&task_memory_allocator)
        , pool(_pool)
    {
    }

    template < class TMemInterface > void base_task_graph< TMemInterface >::setup(sub_graph_type *graph)
    {
        task_vector *task_list;
        if (graph)
        {
            task_list = &(graph->task_list);
        }
        else
        {
            task_list = &(debug.task_list);
        }
        for (auto task : *task_list)
        {
            // memset(&(task->transient), 0x0, sizeof(task_type::transient_container));
            task->transient.start_gate = 0;
            task->transient.num_working = 0;
        }
        for (auto task : *task_list)
        {
            for (auto dependent_task : task->persistent.dependent_tasks)
            {
                ++dependent_task->transient.start_gate;
            }
        }
    }

    template < class TMemInterface > bool base_task_graph< TMemInterface >::find_head(task_vector &_head_list)
    {
        auto found_at_least_one_head = false;
        for (auto task : debug.task_list)
        {
            uint64_t start_gate = task->transient.start_gate.load();
            if (start_gate == 0)
            {
                _head_list.push_back(task);
                found_at_least_one_head = true;
            }
        }
        return found_at_least_one_head;
    }

    template < class TMemInterface > size_t base_task_graph< TMemInterface >::size(task_list _task_list) const
    {
        size_t count = 0;
        task_type *itr = _task_list;
        while (itr)
        {
            count++;
            itr = itr->transient.next_task.load();
        }
        return count;
    }

    template < class TMemInterface > void base_task_graph< TMemInterface >::initialize()
    {
        using namespace std::placeholders;

        // initialize tasks' queue pointers and start gates
        setup();

        // initialize head tasks
        auto found = find_head(persistent.head_tasks);
        // Check if we have at least one head
        assert(found);
        (void)found;

        // Setup end nodes to start head nodes
        setup_tail_kickers();

#if defined(DEBUG)
        // Check if there are more than one tail nodes per head node
        std::set< task_type * > head_nodes_with_a_tail_node;
        for (auto tail_task : tail_tasks)
        {
            for (auto kick_task : tail_task->kick_tasks)
            {
                auto result = head_nodes_with_a_tail_node.insert(kick_task);
                assert(result.second);
            }
        }
#endif // DEBUG

        typedef std::set< task_type *, std::less< task_type * >, stl_allocator< task_type *, TMemInterface > > task_set;

        // Setup Subgraphs
        // Each subgraph has only 1 tail, so we get the heads in the tail to traverse
        // all nodes to build a graph
        for (auto tail_task : persistent.tail_tasks)
        {
            auto *sub_graph = new sub_graph_type();
            sub_graph->tail_tasks.push_back(tail_task);
            task_set sub_graph_set;
            for (auto kick_task : tail_task->persistent.kick_tasks)
            {
                sub_graph->head_tasks.push_back(kick_task);
                void *param = nullptr;
                depth_first_visitor(kick_task, bind(
                                                   [](task_type *node, void *&_param, task_set *_sub_graph_set,
                                                      sub_graph_type *_sub_graph) {
                                                       (void)_param;
                                                       _sub_graph_set->insert(node);
                                                       node->persistent.sub_graph = _sub_graph;
                                                   },
                                                   _1, _2, &sub_graph_set, sub_graph),
                                    nullptr, nullptr, nullptr, param);
            }
            copy(sub_graph_set.begin(), sub_graph_set.end(), back_inserter(sub_graph->task_list));
            persistent.sub_graphs.push_back(sub_graph);
        }

        task_set ranked_tasks;
        traversal_function_type ranking_func = [&](task_type *nodeTask, void *&param) {
            param = (void *)1;
            nodeTask->persistent.rank += reinterpret_cast< typename task_type::rank_type >(param);
            ts_print(nodeTask->debug.task_name << " - rank_type :" << int32_t(nodeTask->persistent.rank));
        };

        // rank_type Nodes
        for (auto sub_graph : persistent.sub_graphs)
        {
            for (auto bottomHeadTask : sub_graph->tail_tasks)
            {
                void *param = nullptr;
                depth_first_visitor(bottomHeadTask, ranking_func, nullptr, nullptr, nullptr, param, true);
            }
        }

        struct rank_sorter
        {
            static bool compare(task_type *&_a, task_type *&_b)
            {
                return (_a->persistent.rank < _b->persistent.rank ? true : false);
            }
        };

        // Sort dependent tasks for each task based on rank
        for (auto &task : debug.task_list)
        {
            sort(task->persistent.dependent_tasks.begin(), task->persistent.dependent_tasks.end(),
                 rank_sorter::compare);
        }

        // Correct thread affinity masks of all tasks
        for (auto head_task : persistent.head_tasks)
        {
            void *param = nullptr;
            depth_first_visitor(head_task,
                                [&](task_type *_task, void *&_param) {
                                    (void)_param;
                                    set_task_thread_affinity(_task, _task->persistent.thread_affinity);
                                },
                                nullptr, nullptr, nullptr, param);
        }
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::set_task_thread_affinity(task_type *_task, thread_mask_int_t _mask)
    {
        _task->persistent.thread_affinity = 0;
        thread_mask_int_t valid_thread_mask = 1ull << pool.num_threads;
        valid_thread_mask = valid_thread_mask - 1;
        while (_mask)
        {
            _task->persistent.thread_affinity |= _mask & valid_thread_mask;
            _mask = _mask >> pool.num_threads;
        }
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::set_task_thread_exclusion(task_type *_task, thread_mask_int_t _mask)
    {
        _mask = ~_mask;
        thread_mask_int_t valid_thread_mask = 1ull << pool.num_threads;
        valid_thread_mask = valid_thread_mask - 1;
        _mask = _mask & valid_thread_mask;
        set_task_thread_affinity(_task, _mask);
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::set_num_workers(task_type *_task, thread_num_t _num_workers)
    {
        _task->persistent.num_workers = min(pool.num_threads, _num_workers);
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::set_percentage_of_workers(task_type *_task, float _percentage_workers)
    {
        assert(_percentage_workers > .0f && _percentage_workers <= 1.0f);
        _task->persistent.num_workers = ceil(_percentage_workers * (float)pool.num_threads);
    }

    template < class TMemInterface > void base_task_graph< TMemInterface >::setup_tail_kickers()
    {
        using namespace std::placeholders;

        for (auto head_task : persistent.head_tasks)
        {
            void *param = nullptr;
            depth_first_visitor(
                head_task, nullptr, nullptr, nullptr,
                bind(
                    [](task_type *_tail_task, void *&_param, task_type *_head_task, task_vector *_tail_tasks) {
                        (void)_param;
                        // Only add unique items
                        auto result = find(begin(*_tail_tasks), end(*_tail_tasks), _tail_task);
                        if (result == end(*_tail_tasks))
                        {
                            _tail_task->persistent.kick_tasks.push_back(_head_task);
                            _tail_tasks->push_back(_tail_task);
                        }
                    },
                    _1, _2, head_task, &persistent.tail_tasks),
                param);
        }
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::depth_first_visitor(task_type *_task,
                                                               traversal_function_type _pre_order_functor,
                                                               traversal_function_type _in_order_functor,
                                                               traversal_function_type _post_order_functor,
                                                               traversal_function_type _tail_functor, void *_param,
                                                               bool _bottom_up)
    {
        if (_pre_order_functor)
            _pre_order_functor(_task, _param);
        if (_bottom_up)
        {
            if (_task->persistent.parent_tasks.size() == 0)
            {
                if (_tail_functor)
                    _tail_functor(_task, _param);
                return;
            }
            for (auto parent_task : _task->persistent.parent_tasks)
            {
                depth_first_visitor(parent_task, _pre_order_functor, _in_order_functor, _post_order_functor,
                                    _tail_functor, _param, _bottom_up);
                if (_in_order_functor)
                    _in_order_functor(_task, _param);
            }
        }
        else
        {
            if (_task->persistent.dependent_tasks.size() == 0)
            {
                if (_tail_functor)
                    _tail_functor(_task, _param);
                return;
            }
            for (auto dependent_task : _task->persistent.dependent_tasks)
            {
                depth_first_visitor(dependent_task, _pre_order_functor, _in_order_functor, _post_order_functor,
                                    _tail_functor, _param, _bottom_up);
                if (_in_order_functor)
                    _in_order_functor(_task, _param);
            }
        }
        if (_post_order_functor)
            _post_order_functor(_task, _param);
    }

    template < class TMemInterface > base_task_graph< TMemInterface >::~base_task_graph()
    {
        for (auto &it : persistent.sub_graphs)
        {
            delete it;
        }
        persistent.sub_graphs.clear();
        for (auto &it : debug.task_list)
        {
            delete it;
        }
        debug.task_list.clear();
    }

    template < class TMemInterface > void base_task_graph< TMemInterface >::kick()
    {
        initialize();
        for (auto head_task : persistent.head_tasks)
        {
            queue_task(head_task);
        }
    }

    template < class TMemInterface >
    void base_task_graph< TMemInterface >::queue_task(task_type *_task, thread_num_t _num_threads_to_wake_up)
    {
        uint32_t priority = _task->persistent.task_priority;
        do
        {
        } while (!transient.task_queue[priority]->push_back(_task) && ++priority < task_type::num_priority);
        assert(priority < task_type::num_priority);

        pool.wake_up(_num_threads_to_wake_up);
    }

    template < class TMemInterface >
    typename base_task_graph< TMemInterface >::task_type *
    base_task_graph< TMemInterface >::dequeue_task(uint32_t _priority)
    {
        task_type *next_task = nullptr;
        transient.task_queue[_priority]->pop_front(next_task);
        return next_task;
    }

    template < class TMemInterface > bool base_task_graph< TMemInterface >::is_task_available()
    {
        for (auto queue : transient.task_queue)
        {
            if (!queue->empty())
            {
                return true;
            }
        }
        return false;
    }

    template < class TMemInterface >
    bool base_task_graph< TMemInterface >::link_task(task_type *_parent_task, task_type *_dependent_task)
    {
        _parent_task->dependent_tasks.push_back(_dependent_task);
        _dependent_task->parent_tasks.push_back(_parent_task);
        return true;
    }
};