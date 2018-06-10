# Task Scheduler
## A C++ 11 Task Scheduler 
- Designed to be a drop in header only task scheduler, although its best to compile it as a lib to reduce compilation times for your project
- A task-stealing scheduler, where worker threads will attempt to steal tasks from its neighbours when its idle
- Each task scedules its dependencies on other free worker queues based on work load estimates
- The scheduler has been optimized to reduce the amount of time spent in the synchronous portion of code
- A graph of tasks and dependencies can be loaded from disk
- Supports task and data parallelism
- Suports task affinities and exclusions
- Scheduler has been optimized for microsecond latency task scheduling on modern cpus
- Tests are included to benchmark the scheduler for various types of workloads
- Support for green threads/fibers will be added in future

[Brief Documentation](docs/index.md)
[Detailed Documentation](https://viknash.github.io/TaskSchedulerDocs/annotated.html)