// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="alignment.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#define ALIGNMENT 16

#pragma pack(ALIGNMENT)
#define class_alignment alignas(ALIGNMENT)