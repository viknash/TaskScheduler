#pragma once

#include <condition_variable>
#include <iomanip>

#include "profile.h"
#include "containers.h"

namespace task_scheduler {

    template <class TMemInterface> class base_task;
    template <class TMemInterface> class base_task_graph;
    template <class TMemInterface> class base_thread_pool;

    typedef uint8_t thread_index_int_t;
    typedef uint64_t thread_mask_int_t;

    template<typename ValueType, class TMemInterface>
    class base_thread_index
    {
        typedef typename base_thread_pool<TMemInterface> thread_pool;

    public:
        base_thread_index(thread_pool* _pool, ValueType _value) :
            pool(*_pool),
            value(_value)
        {
        }

        base_thread_index& operator++()
        {
            *this += 1;
            return *this;
        }

        base_thread_index& operator--()
        {
            *this -= 1;
            return *this;
        }

        base_thread_index& operator+=(const base_thread_index& rhs)
        {
            value = (value + rhs) % pool.num_threads;
            return *this;
        }

        friend base_thread_index operator+(base_thread_index lhs, const base_thread_index& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        base_thread_index& operator-=(const base_thread_index& rhs)
        {
            value = (value + pool.num_threads - rhs) % pool.num_threads;
            return *this;
        }

        base_thread_index& operator-=(int32_t rhs)
        {
            value = (value + pool.num_threads - rhs) % pool.num_threads;
            return *this;
        }

        operator const ValueType()
        {
            return value;
        }

        thread_mask_int_t get_mask()
        {
            return 1ull << value;
        }

    private:
        ValueType value;
        thread_pool& pool;
    };
   
    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType, TMemInterface> operator+(base_thread_index<ValueType, TMemInterface> lhs, const base_thread_index<ValueType, TMemInterface>& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType, TMemInterface> operator+(base_thread_index<ValueType, TMemInterface> lhs, int32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType, TMemInterface> operator+(int32_t lhs, const base_thread_index<ValueType, TMemInterface>& rhs)
    {
        return rhs + lhs;
    }

    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType,TMemInterface> operator-(base_thread_index<ValueType, TMemInterface> lhs, const base_thread_index<ValueType, TMemInterface>& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    
    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType, TMemInterface> operator-(base_thread_index<ValueType, TMemInterface> lhs, int32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    template<typename ValueType, class TMemInterface>
    inline base_thread_index<ValueType, TMemInterface> operator-(int32_t lhs, const base_thread_index<ValueType, TMemInterface>& rhs)
    {
        return rhs - lhs;
    }

    template<class TMemInterface>
    using thread_index_t = base_thread_index<thread_index_int_t, TMemInterface>;

    template <class TMemInterface>
    struct base_thread : public TMemInterface
    {
        typedef typename base_task_graph<TMemInterface> task_graph_type;
        typedef typename task_graph_type::task_type task_type;
        typedef typename task_graph_type::task_queue_type task_queue_type;
        typedef typename base_thread<TMemInterface> thread_type;
        typedef typename base_thread_pool<TMemInterface> thread_pool;
        typedef typename task_graph_type::task_memory_allocator_type task_memory_allocator_type;
        typedef typename thread_index_t<TMemInterface> thread_index_type;

        base_thread(uint8_t _thread_index, thread_pool* _pool);
        ~base_thread();

        static thread_type* create_thread(thread_pool* _pool);

        void sleep(bool(thread_type::*_wake_up)());
        void wake_up();
        void join();

        task_queue_type*  task_queue[task_type::NUM_PRIORITY];
        thread_index_type thread_index;
        std::thread::id  thread_id;
        std::thread      task_thread;
        task_memory_allocator_type allocator;

        friend class std::thread;

    private:
        void init();
        void run();
        bool is_task_available();
        task_type* get_task();

        thread_pool& pool;
        std::mutex signal;
        std::condition_variable radio;
    };

    template <class TMemInterface>
    base_thread<TMemInterface>::base_thread(uint8_t _thread_index, thread_pool* _pool) :
        thread_index(_pool, _thread_index),
        pool(*_pool)
    {
        for (auto& queue : task_queue)
        {
            queue = new task_queue_type(&allocator);
        }

        task_thread = std::thread([&] {
            init();
            run();
        });
    }

    template <class TMemInterface>
    base_thread<TMemInterface>::~base_thread()
    {
        for (auto& queue : task_queue)
        {
            delete queue;
            queue = nullptr;
        }
    }

    template <class TMemInterface>
    base_thread<TMemInterface>* base_thread<TMemInterface>::create_thread(thread_pool* _pool)
    {
        static uint8_t next_thread_num = 0;
        return new thread_type(next_thread_num++, _pool);
    }

    template <class TMemInterface>
    void base_thread<TMemInterface>::init()
    {
        thread_id = std::this_thread::get_id();
        pool.current_thread = this;

        // Signal thread_type has started
        --pool.setup.thread_sync;
        pool.setup.radio.notify_one();

        //wake_up when all threads have started
        unique_lock<mutex> signalLock(signal);
        radio.wait(signalLock);
    }

    template <class TMemInterface>
    void base_thread<TMemInterface>::sleep(bool (thread_type::*_wake_up)())
    {
        unique_lock<mutex> signal_lock(signal);
        while (!(this->*_wake_up)() && pool.setup.request_exit != thread_pool::request_stop)
        {
            radio.wait(signal_lock);
        }
    }

    template <class TMemInterface>
    void base_thread<TMemInterface>::wake_up()
    {
        unique_lock<mutex> signal_lock(signal);
        radio.notify_one();
    }

    template <class TMemInterface>
    void base_thread<TMemInterface>::join()
    {
        task_thread.join();
    }

    template <class TMemInterface>
    bool base_thread<TMemInterface>::is_task_available()
    {
        for (auto queue : task_queue)
        {
            if (!queue->empty())
            {
                return true;
            }
        }

        return  pool.task_graph->is_task_available();
    }

    template <class TMemInterface>
    void base_thread<TMemInterface>::run()
    {
        profile_time scheduling(0ms), sleeping(0ms), working(0ms);

        std::cout << "Starting thread_type " << uint32_t(thread_index) << std::endl;

        while (pool.setup.request_exit != thread_pool::request_stop)
        {
            //Steal task_type
            task_type* run_task = instrument<task_type*, thread_type, task_type*(thread_type::*)()>(scheduling, this, &thread_type::get_task);

            if (run_task)
            {
                //Run task_type
                profile_time task_time(0ms);
                ++pool.num_working;
                instrument<void, task_type, void(task_type::*)()>(task_time, run_task, &task_type::operator());
                --pool.num_working;
                std::cout << "thread_type(" << uint32_t(thread_index) << "), task_type " << run_task->debug.task_name << "(" << chrono::duration_cast<chrono::milliseconds>(task_time).count() << "ms)" << std::endl;
                working += task_time;

                //Donate More Tasks
                instrument<void, task_type, void(task_type::*)()>(scheduling, run_task, &task_type::kick_dependent_tasks);
            }
            else if (!is_task_available())
            {
                //Go to sleep if there is no task to run
                instrument<void, thread_type, void(thread_type::*)(bool(thread_type::*)()) >(sleeping, this, &thread_type::sleep, &thread_type::is_task_available);
            }
        };

        assert(!is_task_available());

        auto scheduling_ms = chrono::duration_cast<chrono::milliseconds>(scheduling);
        auto sleeping_ms = chrono::duration_cast<chrono::milliseconds>(sleeping);
        auto working_ms = chrono::duration_cast<chrono::milliseconds>(working);
        auto scheduling_ratio = double(working.count() / (scheduling.count() == 0 ? 1 : scheduling.count()));
        std::cout << "thread_type " << uint32_t(thread_index) << " Complete, Scheduling Overhead=" << scheduling_ms.count() << "ms, sleep Time=" << sleeping_ms.count() << "ms, Work Time=" << working_ms.count() << "ms, Work/Schedule Ratio=" << fixed << setprecision(0) << scheduling_ratio << std::endl;
    }

    template <class TMemInterface>
    typename base_thread<TMemInterface>::task_type* base_thread<TMemInterface>::get_task()
    {
        task_type *next_task = nullptr;
        for (uint32_t priority = 0; priority < task_type::NUM_PRIORITY; priority++)
        {
            //Try to get a task from the thread queue
            if (task_queue[priority]->pop_front(next_task))
            {
                break;
            }

            //Try to get a new manually scheduled task from the global queue
            next_task = pool.task_graph->dequeue_task(priority);
            if (next_task)
            {
                pool.queue_rank[priority][thread_index].fetch_add(next_task->persistent.rank);
                break;
            }

            //Try to steal task from other threads, starting from the previous thread
            //In practice the spinning of the lock free queue, in a way locks the current thread we are trying to steal from
            //Disabling thread affinities will make the stealing much more efficient
            thread_index_type current_thread_index = thread_index - 1;
            do {
                task_type *stolen_task = nullptr;
                task_queue_type temporary_queue(&(pool.threads[current_thread_index]->allocator));
                do {
                    if (pool.threads[current_thread_index]->task_queue[priority]->pop_front(stolen_task))
                    {
                        if (stolen_task->persistent.thread_affinity & current_thread_index.get_mask())
                        {
                            //Stole a task
                            next_task = stolen_task;
                            break;
                        }
                        else
                        {
                            temporary_queue.push_back(stolen_task);
                        }
                    }
                } while (!pool.threads[current_thread_index]->task_queue[priority]->empty());

                while (!temporary_queue.empty())
                {
                    pool.threads[current_thread_index]->task_queue[priority]->push_back(stolen_task);
                }

                if (next_task)
                {
                    break;
                }

                --current_thread_index;
            } while (current_thread_index != thread_index);
        }

        return next_task;
    }

};