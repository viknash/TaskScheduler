// ***********************************************************************
// Assembly         : task_scheduler
// Author           : viknash
// ***********************************************************************
// <copyright file="main.cpp" >
//     Copyright (c) viknash. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "stdafx.h"

#include <algorithm>
#include <random>

#include "containers.h"
#include "profile.h"
#include "task.h"
#include "taskgraph.h"
#include "thread.h"
#include "threadpool.h"
#include "utils.h"

#include "gtest/gtest.h"

using namespace task_scheduler;
using namespace std;

task_scheduler_static_data();

namespace
{
    class MultiThreadedDetectorTest : public ::testing::Test
    {
      protected:
        virtual void SetUp() {}

        virtual void TearDown() {}

        thread_unsafe_access_storage detector;
        thread_unsafe_access_storage detector2;
        thread test_thread[2];
        atomic_uint32_t thread_sync;
        std::mutex thread_signal[2];
        std::condition_variable thread_radio[2];
        std::mutex pool_signal;
        std::condition_variable pool_radio;
    };

    TEST_F(MultiThreadedDetectorTest, RecursiveAccess)
    {
        unsafe_multi_threaded_access_detector< thread_unsafe_access_storage > guard1, guard2;
        EXPECT_TRUE(guard1.enter(detector));
        EXPECT_TRUE(guard2.enter(detector));
        EXPECT_TRUE(guard2.exit(detector));
        EXPECT_TRUE(guard1.exit(detector));
    }

    TEST_F(MultiThreadedDetectorTest, BadRecursiveAccess)
    {
        unsafe_multi_threaded_access_detector< thread_unsafe_access_storage > guard1, guard2;
        EXPECT_TRUE(guard1.enter(detector));
        EXPECT_TRUE(guard2.exit(detector));
        EXPECT_TRUE(guard2.enter(detector));
        EXPECT_TRUE(guard1.exit(detector));
    }

    TEST_F(MultiThreadedDetectorTest, SimultaneousAccess)
    {
        bool enter[2], exit[2];
        thread_sync = 2;
        test_thread[0] = std::thread([&] {
            unsafe_multi_threaded_access_detector< thread_unsafe_access_storage > guard;
            --thread_sync;
            pool_radio.notify_one();
            {
                unique_lock< mutex > signalLock(thread_signal[0]);
                thread_radio[0].wait(signalLock);
            }

            enter[0] = guard.enter(detector2);
            exit[0] = guard.exit(detector2);

            --thread_sync;
            pool_radio.notify_one();
            {
                unique_lock< mutex > signalLock(thread_signal[0]);
                thread_radio[0].wait(signalLock);
            }

        });
        test_thread[1] = std::thread([&] {
            unsafe_multi_threaded_access_detector< thread_unsafe_access_storage > guard;
            --thread_sync;
            pool_radio.notify_one();
            {
                unique_lock< mutex > signalLock(thread_signal[1]);
                thread_radio[1].wait(signalLock);
            }

            enter[1] = guard.enter(detector2);
            exit[1] = guard.exit(detector2);

            --thread_sync;
            pool_radio.notify_one();

            {
                unique_lock< mutex > signalLock(thread_signal[0]);
                thread_radio[0].wait(signalLock);
            }
        });

        // Wait until all threads are started
        while (thread_sync != 0)
        {
            unique_lock< mutex > signal(pool_signal);
            pool_radio.wait(signal);
        }

        thread_sync = 2;
        {
            unique_lock< mutex > signal_lock(thread_signal[0]);
            thread_radio[0].notify_one();
        }
        {
            unique_lock< mutex > signal_lock(thread_signal[1]);
            thread_radio[1].notify_one();
        }

        // Wait until all threads are started
        while (thread_sync != 0)
        {
            unique_lock< mutex > signal(pool_signal);
            pool_radio.wait(signal);
        }

        {
            unique_lock< mutex > signal_lock(thread_signal[0]);
            thread_radio[0].notify_one();
        }
        {
            unique_lock< mutex > signal_lock(thread_signal[1]);
            thread_radio[1].notify_one();
        }

        // Both threads did not execute simultaneously
        if (enter[0] && exit[0])
        {
            ASSERT_TRUE(enter[1]);
            ASSERT_TRUE(exit[1]);
        }
        if (enter[0] && !enter[1])
        {
            ASSERT_TRUE(!exit[0]);
            ASSERT_TRUE(!exit[1]);
        }
        if (!enter[0] && enter[1])
        {
            ASSERT_TRUE(!exit[0]);
            ASSERT_TRUE(!exit[1]);
        }
    }
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
