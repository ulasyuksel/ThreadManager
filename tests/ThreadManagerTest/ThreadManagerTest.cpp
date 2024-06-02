/*
 * ThreadManager_test.cpp
 *
 *  Created on: June 1, 2024
 *      Author: ulasy
 */

#include "TaskThread.hpp"
#include "ThreadManager.hpp"
#include "ThreadState.hpp"
#include "FirstJob.hpp"
#include "SecondJob.hpp"
#include <memory> 
#include <gtest/gtest.h>

static const unsigned int max_thread = 4;

class ThreadManagerTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ThreadManagerTest() {
     // You can do set-up work for each test here.
  }

  ~ThreadManagerTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }
};

TEST_F(ThreadManagerTest, ThreadManagerTestAll)
{
   ThreadManager my_local_thread_manager(max_thread);
    //check size
    EXPECT_EQ(max_thread,my_local_thread_manager.size());

    for (unsigned int thread_id = 0; thread_id < max_thread; thread_id++)
    {
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::IDLE);
    }

    //if id is out of bound status should be UNKNOWN
    EXPECT_EQ(my_local_thread_manager.status(max_thread), ThreadState::UNKNOWN);

    //register jobs
    for (unsigned int thread_id = 0; thread_id < max_thread; thread_id++)
    {
        if (thread_id%2)
        {
            std::unique_ptr<AnyJob> ret = std::make_unique<FirstJob>();
            my_local_thread_manager.registerJob(thread_id, ret);
        }
        else
        {
            std::unique_ptr<AnyJob> ret = std::make_unique<SecondJob>();
            my_local_thread_manager.registerJob(thread_id, ret);
        }
    }

    //For each of the Threads check states
    for (unsigned int thread_id = 0; thread_id < max_thread; thread_id++)
    {
        //Should be still idle
        my_local_thread_manager.pause(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::IDLE);

        //Should be still idle
        my_local_thread_manager.resume(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::IDLE);

        my_local_thread_manager.start(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::RUNNING);

        //Should be still running
        my_local_thread_manager.resume(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::RUNNING);

        //Should be paused
        my_local_thread_manager.pause(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::PAUSED);

        //Should be still running
        my_local_thread_manager.resume(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::RUNNING);

        //Aborted thread can not change state.
        my_local_thread_manager.abort(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::ABORTED);

        my_local_thread_manager.resume(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::ABORTED);

        my_local_thread_manager.pause(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::ABORTED);

        my_local_thread_manager.start(thread_id);
        EXPECT_EQ(my_local_thread_manager.status(thread_id), ThreadState::ABORTED);
    }

}