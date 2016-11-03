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
1. Convert LockFreeNodes+Tasks to an Intrusive list
2. Create one dispenser for all tasks
3. Hookup all classes to the same interface
4. Implement Thread Memory Allocators
5. Implement Thread Memory Reclamation Lock Free List
6. Run Thread Memory Reclamation before thread sleeps and periodically
7. Remove central task queue in task graph
8. Implement queue ranking
9. KickDependentTasks will select thread based on thread ranking
10. Implement Ranking for each task based on their the cumulative number of dependents
11. Process KickDependentTasks based on ranking
12. Augment ranking with heuristics based on last execution time for a task
13. Implement data parallel tasks
14. Implement parent task pointer
15. Implement natvis for taskgraph, lockfree queue
16. Implement stl allocators for vectors
17. Assert on global new and delete

To Test
1. Test allocator alignment
2. 