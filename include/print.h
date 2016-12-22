#pragma once

#include <cstdint>
#include <thread>
#include <atomic>
#include <iostream>
#include <sstream>
#include <mutex>

#include "utils.h"
#include "globals.h"
#include "platform.h"

#if !defined(TASK_SCHEDULER_DEBUG)
#error("TASK_SCHEDULER_DEBUG is not defined")
#endif// !defined(TASK_SCHEDULER_DEBUG)

namespace task_scheduler {

#if defined(TASK_SCHEDULER_DEBUG)
    struct out_t {
        template<typename T>
        out_t& operator << (T&& x) {
            buffer << x;
            return *this;
        };

        out_t() {
            buffer << thread_name << "> ";
        }

        ~out_t() {
            std::lock_guard<std::mutex> lk(globals.io_mutex);
            ts_windows_only(SetConsoleTextAttribute(globals.console_handle, get_thread_number()););
            std::cout << buffer.str() << std::endl;
        }

        std::ostringstream buffer;
    };
#else //defined(TASK_SCHEDULER_DEBUG)
    struct out_t {
        template<typename T>
        out_t& operator << (T&& x) {
            return *this;
        };
    };
#endif //defined(TASK_SCHEDULER_DEBUG)


#define task_scheduler_static_data() \
    namespace task_scheduler { \
            static_data_t globals; \
    };

#define ts_print_internal(arg) out_t arg; arg

#define ts_print(x) { \
        ts_print_internal(ts_unique_variable(printout)) << x;\
    }

};