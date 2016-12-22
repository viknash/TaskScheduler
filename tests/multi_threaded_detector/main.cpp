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

task_scheduler_default_mem_interface_catch_all_allocations();
task_scheduler_static_data();


TEST(SquareRootTest, ZeroAndNegativeNos) {
    EXPECT_EQ(0.0, 0.0);
    EXPECT_EQ(-1, -1);
}

int main()
{

    system("pause");
    return 0;
}
