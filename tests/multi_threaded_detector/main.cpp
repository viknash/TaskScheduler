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

namespace {
    class MultiThreadedDetectorTest : public ::testing::Test {
    protected:
       virtual void SetUp() {
       }

       virtual void TearDown() {
       }

       thread_unsafe_access_storage detector;
    };

    TEST_F(MultiThreadedDetectorTest, RecursiveAccess) {
        unsafe_multi_threaded_access_detector<thread_unsafe_access_storage> guard1, guard2;
        EXPECT_TRUE(guard1.enter(detector));
        EXPECT_TRUE(guard2.enter(detector));
        EXPECT_TRUE(guard2.exit(detector));
        EXPECT_TRUE(guard1.exit(detector));
    }

    TEST_F(MultiThreadedDetectorTest, BadRecursiveAccess) {
        unsafe_multi_threaded_access_detector<thread_unsafe_access_storage> guard1, guard2;
        EXPECT_TRUE(guard1.enter(detector));
        EXPECT_TRUE(guard2.exit(detector));
        EXPECT_TRUE(guard2.enter(detector));
        EXPECT_TRUE(guard1.exit(detector));
    }

};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
