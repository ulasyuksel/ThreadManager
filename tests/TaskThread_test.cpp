/*
 * TaskThread_test.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#include "../TaskThread.hpp"
#include "../ThreadState.hpp"
#include "../FirstJob.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

// ALEPH_ASSERT_EQUAL From: https://bastian.rieck.me/blog/posts/2017/simple_unit_tests/
// Can be moved to a header.

#define ALEPH_ASSERT_EQUAL( x, y )                                  \
{                                                                   \
  if( ( x ) != ( y ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    );                                                              \
  }                                                                 \
}


int main(int argc, char **argv)
{
    //check ID
    TaskThread thread(3);
    ALEPH_ASSERT_EQUAL((unsigned)3,(unsigned)thread.id());
    //check initial state, IDLE
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::IDLE);

    //Should be still idle
    thread.pause();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::IDLE);

    //Should be still idle
    thread.resume();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::IDLE);

    std::unique_ptr<AnyJob> ret = std::make_unique<FirstJob>();
    thread.registerJob(ret);
    thread.start();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::RUNNING);

    //Should be still running
    thread.resume();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::RUNNING);

    //Should be paused
    thread.pause();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::PAUSED);

    //Should be still running
    thread.resume();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::RUNNING);

    //Aborted thread can not change state.
    thread.abort();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::ABORTED);

    thread.resume();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::ABORTED);

    thread.pause();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::ABORTED);

    thread.start();
    ALEPH_ASSERT_EQUAL((unsigned)thread.status(),(unsigned)ThreadState::ABORTED);

}
