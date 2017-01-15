// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="concurrency.h" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <cstdint>
#include <mutex>

#include "platform.h"
#include "print.h"

/// <summary>
/// The task_scheduler namespace.
/// </summary>
namespace task_scheduler
{
    class event
    {
    public:
        void signal();
        void wait();

    protected:
        /// <summary>
        /// The signal
        /// </summary>
        std::mutex lock;
        /// <summary>
        /// The radio
        /// </summary>
        std::condition_variable cond_var;
    };

    inline void event::signal()
    {
        cond_var.notify_one();
    }

    inline void event::wait()
    {
        std::unique_lock< std::mutex > signal_lock(lock);
        cond_var.wait(signal_lock);
    }

    class alarm : protected event
    {
    public :
        typedef std::function<bool()> wake_up_function;
        alarm();
        void sleep(wake_up_function _wake_up_func);
        void wake_up();
    protected:
        bool sleeping;
    };

    inline alarm::alarm() :
        sleeping(false)
    {
        
    }

    inline void alarm::sleep(wake_up_function _wake_up_func)
    {
        std::unique_lock< std::mutex > signal_lock(lock);
        while (!_wake_up_func)
        {
            ts_print("sleep");
            sleeping = true;
            cond_var.wait(signal_lock);
            sleeping = false;
            ts_print("awake");
        }
    }

    inline void alarm::wake_up()
    {
        lock.lock();
        if (sleeping)
        {
            lock.unlock();
            cond_var.notify_one();
        }
        else
        {
            lock.unlock();
        }
    }

};