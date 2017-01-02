// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="cache.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <cinttypes>

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{

    /// <summary>
    /// Gets the size of the cache line.
    /// </summary>
    /// <returns>uint32_t.</returns>
    uint32_t get_cache_line_size() { return 64; }
};