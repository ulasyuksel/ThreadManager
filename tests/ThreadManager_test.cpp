/*
 * ThreadManager_test.cpp
 *
 *  Created on: May 2, 2021
 *      Author: ulasy
 */

#include "../TaskThread.hpp"
#include "../ThreadManager.hpp"
#include "../ThreadState.hpp"
#include "../FirstJob.hpp"
#include "../SecondJob.hpp"
#include "unit_tests.h"
   static const unsigned int max_thread = 4;

int main(int argc, char **argv)
{

    ThreadManager my_local_thread_manager(max_thread);
    //check size
    ALEPH_ASSERT_EQUAL(max_thread,my_local_thread_manager.size());

    for (unsigned int thread_id = 0; thread_id < max_thread; thread_id++)
    {
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id), (unsigned)ThreadState::IDLE);
    }

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
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::IDLE);

        //Should be still idle
        my_local_thread_manager.resume(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::IDLE);

        my_local_thread_manager.start(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::RUNNING);

        //Should be still running
        my_local_thread_manager.resume(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::RUNNING);

        //Should be paused
        my_local_thread_manager.pause(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::PAUSED);

        //Should be still running
        my_local_thread_manager.resume(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::RUNNING);

        //Aborted thread can not change state.
        my_local_thread_manager.abort(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::ABORTED);

        my_local_thread_manager.resume(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::ABORTED);

        my_local_thread_manager.pause(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::ABORTED);

        my_local_thread_manager.start(thread_id);
        ALEPH_ASSERT_EQUAL((unsigned)my_local_thread_manager.status(thread_id),(unsigned)ThreadState::ABORTED);
    }

}


