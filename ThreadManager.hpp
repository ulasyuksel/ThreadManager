/*
 * ThreadManager.hpp
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#ifndef THREADMANAGER_HPP_
#define THREADMANAGER_HPP_

#include "TaskThread.hpp"
#include  <memory>
#include  <vector>
class ThreadManager {
public:
    ThreadManager(unsigned int size);
    ~ThreadManager();

    /**
     * Get status of task with given id
     */
    ThreadState status(unsigned int id);

    /**
     * Start task with given id if task is idle.
     */
    void start(unsigned int id);

    /**
     * Pause task with given id if task is running.
     */
    void pause(unsigned int id);

    /**
     * Cancel task with given id.
     */
    void abort(unsigned int id);

    /**
     * Resume task with given id if task is paused.
     */
    void resume(unsigned int id);

    /**
     * Number of threads in pool.
     */
    unsigned int size();

    void setTask(unsigned int id, std::function<bool()> task_func);

private:

    ///vector to store TaskThreads
    std::vector<std::unique_ptr<TaskThread>> m_task_thread_vector;
};

#endif /* THREADMANAGER_HPP_ */
