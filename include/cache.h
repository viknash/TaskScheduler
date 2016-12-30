#pragma once

#include <cinttypes>

namespace task_scheduler {

    uint32_t get_cache_line_size()
    {
        return 64;
    }
};