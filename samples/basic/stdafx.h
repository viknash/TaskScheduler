
#include "targetver.h"

#include "defines.h"

#if defined(_DEBUG)
#define TASK_SCHEDULER_DEBUG TASK_SCHEDULER_ENABLED
#else
#define TASK_SCHEDULER_DEBUG TASK_SCHEDULER_DISABLED
#endif // defined(_DEBUG)
#define TASK_SCHEDULER_ASSERT TASK_SCHEDULER_ENABLED
#define TASK_SCHEDULER_PROFILER TASK_SCHEDULER_PROFILER_NONE
