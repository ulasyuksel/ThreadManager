/*
 * ThreadState.hpp
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#ifndef THREADSTATE_HPP_
#define THREADSTATE_HPP_

enum class ThreadState
{
    ///initial state before run
    IDLE,
    ///task is running
    RUNNING,
    ///task is paused
    PAUSED,
    ///task is aborted. can not be run again
    ABORTED,
    ///unknown state
    UNKNOWN
};

/**
 * This function converts ThreadState to a string.
 *
 */
inline std::string threadStateToString(ThreadState state)
{
    switch (state) {
        case ThreadState::IDLE:
            return "IDLE";
        case ThreadState::RUNNING:
            return "RUNNING";
        case ThreadState::PAUSED:
            return "PAUSED";
        case ThreadState::ABORTED:
            return "ABORTED";
    }
    return "UNKNOWN";
}

#endif /* THREADSTATE_HPP_ */
