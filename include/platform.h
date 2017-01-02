// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="platform.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__CYGWIN__) ||                   \
    defined(__MINGW32__) || defined(__BORLANDC__)
#define ts_windows 1
#endif

#if !defined(TASK_SCHEDULER_DEBUG)
#error("TASK_SCHEDULER_DEBUG is not defined")
#endif // !defined(TASK_SCHEDULER_DEBUG)

#if defined(ts_windows)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif //! defined(NOMINMAX)
struct IUnknown;
#include <Unknwnbase.h>
#include <windows.h>
#endif

#if defined(ts_windows)
#define ts_windows_only(x) x
#else // defined(ts_windows)
#define ts_windows_only(x)
#endif // defined(ts_windows)
