/*
 * TaskThread.h
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#ifndef TASKTHREAD_HPP_
#define TASKTHREAD_HPP_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <thread>
#include "ThreadState.hpp"
#include "AnyJob.hpp"


class TaskThread {
public:
    TaskThread(unsigned int id);
    ~TaskThread();

    /**
     * Set task.
     *
     * @param register job to task.
     */
    void registerJob(std::unique_ptr<AnyJob> &job);

    /**
     * Get status of task.
     */
    ThreadState status();

    /**
     * Start task if task is idle.
     */
    void start();

    /**
     * Pause task if task is running.
     */
    void pause();

    /**
     * Abort task. Thread will be ready for join.
     */
    void abort();

    /**
     * Resume task if task is paused.
     */
    void resume();

    /**
     * Get task id.
     */
    unsigned int id();

private:
    /**
     * method for running thread.
     */
    void internalTask();

    std::thread m_thread;

    /// The task
    std::function<bool()> m_task_func;

    /// Mutex for thread loop.
    std::mutex m_mutex;

    /// Condition variable to wake up thread from pause or idle states.
    std::condition_variable m_state_changed;

    /// Thread ID.
    unsigned int m_id;

    /// Thread state.
    std::atomic<ThreadState> m_state;

    /// Job to run.
    std::unique_ptr<AnyJob> m_job;
};

#endif /* TASKTHREAD_HPP_ */
