#pragma once

#include <cstdint>
#include <thread>
#include <atomic>

#include "platform.h"
#include "types.h"

namespace task_scheduler {

    const thread_num_t max_num_threads = 64;

    struct static_data_t
    {
        std::mutex io_mutex;
        HANDLE console_handle;
        std::atomic<thread_num_t> next_thread_number;
        static_data_t() :
            next_thread_number(1),
            console_handle(0)
        {
            console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        }
    };

    extern static_data_t globals;

    thread_local std::string thread_name;
    thread_local thread_num_t thread_unique_number;

    uint8_t get_thread_number()
    {
        if (!thread_unique_number)
        {
            thread_unique_number = ++globals.next_thread_number;
        }
        return thread_unique_number;
    }

#define task_scheduler_static_data() \
    namespace task_scheduler { \
            static_data_t globals; \
    };

}