// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="profile.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <thread>

#include "utils.h"
#include "containers.h"

#include "internal/profilebase.h"

#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_NONE
#include "internal/profilenone.h"
#endif
#if TASK_SCHEDULER_PROFILER == TASK_SCHEDULER_PROFILER_ITT
#include "internal/profileitt.h"
#endif
