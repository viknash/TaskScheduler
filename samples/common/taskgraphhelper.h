// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="taskgraphhelper.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
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

    template < class TMemInterface > class base_thread_pool;

    template < class TMemInterface > class base_task_graph_helper : public TMemInterface
    {
      public:
        typedef typename base_task<TMemInterface>::task_type task_type;
        typedef typename base_worker_task<TMemInterface>::worker_task_type worker_task_type;

        typedef std::basic_string< char, std::char_traits< char >, stl_allocator< char, TMemInterface > > string_type;
        typedef std::vector< task_type *, stl_allocator< task_type *, TMemInterface > > task_vector;
        typedef base_thread_pool< TMemInterface > thread_pool;
        typedef task_type *task_list;
        typedef std::function< void(task_type *, void *&) > traversal_function_type;
        typedef base_task_graph< TMemInterface > task_graph_type;

      public:
          /// <summary>
          /// Initializes a new instance of the <see cref="base_task_graph_helper"/> class.
          /// </summary>
          /// <param name="_task_graph">The task graph.</param>
          base_task_graph_helper(task_graph_type &_task_graph);

          /// <summary>
          /// Loads the specified file name.
          /// </summary>
          /// <param name="_file_name">Name of the file.</param>
          void load(string_type _file_name);
          /// <summary>
          /// Setups the task.
          /// </summary>
          /// <param name="_task">The task.</param>
          /// <param name="_task_file_field">The task file field.</param>
          /// <param name="str">The string.</param>
          void setup_task(task_type *_task, uint32_t _task_file_field, string_type str);

          /// <summary>
          /// The task graph
          /// </summary>
          task_graph_type &task_graph;
    };

    template < class TMemInterface >
    base_task_graph_helper< TMemInterface >::base_task_graph_helper(task_graph_type &_task_graph)
        : task_graph(_task_graph)
    {
    }

    template < class TMemInterface > void base_task_graph_helper< TMemInterface >::load(string_type _file_name)
    {
        using namespace std::placeholders;

        string_type line;
        std::ifstream task_file(_file_name.c_str(), std::ios::in);
        assert(task_file.is_open()); // File was not found
        while (getline(task_file, line))
        {
            typedef std::basic_istringstream< char, std::char_traits< char >, stl_allocator< char, TMemInterface > >
                istringstream_type;
            istringstream_type iss(line);
            string_type token;
            auto new_task = new worker_task_type(task_graph);
            unsigned int _task_file_field = 0;
            while (getline(iss, token, ','))
            {
                std::cout << token << std::endl;
                setup_task(new_task, _task_file_field, token);
                _task_file_field++;
            }
            task_graph.debug.task_name_to_task.insert({new_task->debug.task_name, new_task});
            task_graph.debug.task_list.push_back(new_task);
        }

        for (auto &task : task_graph.debug.task_list)
        {
            for (auto &task_name : task->debug.dependent_task_names)
            {
                auto dependent_task = task_graph.debug.task_name_to_task.find(task_name);
                if (dependent_task != task_graph.debug.task_name_to_task.end())
                {
                    task->persistent.dependent_tasks.push_back(dependent_task->second);
                    dependent_task->second->persistent.parent_tasks.push_back(task);
                }
                else
                {
                    std::cout << "Cannot link" << task->debug.task_name << " to " << task_name << '\n';
                }
            }
        }
    }

    template < class TMemInterface >
    void base_task_graph_helper< TMemInterface >::setup_task(task_type *_task, uint32_t _task_file_field,
                                                             string_type _str)
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

        switch (_task_file_field)
        {
            case TaskName:
                _task->debug.task_name = _str;
                break;
            case TaskPriority:
            {
                transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
                for (auto i = 0; i < task_type::num_priority; i++)
                {
                    if (_str.compare(_task->debug.priority_to_string(
                            static_cast< typename task_type::priority_selector >(i))) == 0)
                    {
                        _task->persistent.task_priority = static_cast< typename task_type::priority_selector >(i);
                    }
                }
                break;
            }
            default:
                _task->debug.dependent_task_names.push_back(_str);
                break;
        }
    }
};