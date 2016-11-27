========================================================================
    CONSOLE APPLICATION : TaskScheduler Project Overview
========================================================================

AppWizard has created this Practice application for you.

This file contains a summary of what you will find in each of the files that
make up your Practice application.


TaskScheduler.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

TaskScheduler.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

main.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

stdafx.h, stdafx.cpp
    These files are used to build a precompiled header (PCH) file
    named TaskScheduler.pch and a precompiled types file named stdafx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

To Do
2. Create one dispenser for all tasks
4. Implement thread_type Memory Allocators
5. Implement thread_type Memory Reclamation Lock Free List
6. Run thread_type Memory Reclamation before thread sleeps and periodically
12. Augment ranking with heuristics based on last execution time for a task
13. Implement data parallel tasks
14. Implement natvis for taskgraph, lockfree queue
16. http://www.codeproject.com/Tips/1055834/Cross-platform-Visual-Memory-Tracker
17. parallel for

To Test
1. Test allocator alignment
2. Test Ranking and parent task pointer
3. Test task dependents sorting