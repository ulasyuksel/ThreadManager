/*
 * TaskThread_test.cpp
 *
 *  Created on: June 1, 2024
 *      Author: ulasy
 */

#include "TaskThread.hpp"
#include "ThreadState.hpp"
#include "FirstJob.hpp"
#include <memory> 
#include <gtest/gtest.h>

class TaskThreadTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TaskThreadTest() {
     // You can do set-up work for each test here.
  }

  ~TaskThreadTest() override {
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

TEST_F(TaskThreadTest, TaskThreadTestAll)
{
    //check ID
    TaskThread thread(3);
    EXPECT_EQ(3, thread.id());
    //check initial state, IDLE
    EXPECT_EQ(thread.status(), ThreadState::IDLE);

    //Should be still idle
    thread.pause();
    EXPECT_EQ(thread.status(), ThreadState::IDLE);

    //Should be still idle
    thread.resume();
    EXPECT_EQ(thread.status(), ThreadState::IDLE);

    std::unique_ptr<AnyJob> ret = std::make_unique<FirstJob>();
    thread.registerJob(ret);
    thread.start();
    EXPECT_EQ(thread.status(), ThreadState::RUNNING);

    //Should be still running
    thread.resume();
    EXPECT_EQ(thread.status(), ThreadState::RUNNING);

    //Should be paused
    thread.pause();
    EXPECT_EQ(thread.status(), ThreadState::PAUSED);

    //Should be still running
    thread.resume();
    EXPECT_EQ(thread.status(), ThreadState::RUNNING);

    //Aborted thread can not change state.
    thread.abort();
    EXPECT_EQ(thread.status(), ThreadState::ABORTED);

    thread.resume();
    EXPECT_EQ(thread.status(), ThreadState::ABORTED);

    thread.pause();
    EXPECT_EQ(thread.status(), ThreadState::ABORTED);

    thread.start();
    EXPECT_EQ(thread.status(), ThreadState::ABORTED);
}