/*
 * TaskThread.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#include "TaskThread.hpp"

TaskThread::TaskThread(unsigned int id) :
        m_state(ThreadState::IDLE),
        m_id(id),
        m_task_func(nullptr)
{
    m_thread = std::thread{std::bind(&TaskThread::internalTask, this)};
}

TaskThread::~TaskThread() {
    m_state = ThreadState::ABORTED;
    m_state_changed.notify_one();
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void TaskThread::start()
{
    if (m_state == ThreadState::IDLE)
    {
        m_state = ThreadState::RUNNING;
        m_state_changed.notify_one();
    }
}

void TaskThread::abort()
{
    m_state = ThreadState::ABORTED;
    m_state_changed.notify_one();
}

void TaskThread::pause()
{
    if (m_state == ThreadState::RUNNING)
    {
        m_state = ThreadState::PAUSED;
    }
}

void TaskThread::resume()
{
    if (m_state == ThreadState::PAUSED)
    {
        m_state = ThreadState::RUNNING;
        m_state_changed.notify_one();
    }
}

unsigned int TaskThread::id()
{
    return m_id;
}

ThreadState TaskThread::status()
{
    return m_state;
}

void TaskThread::registerJob(std::unique_ptr<AnyJob>& job)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_job = std::move(job);
}

void TaskThread::internalTask() {
    std::unique_lock<std::mutex> lock(m_mutex);
    do
    {
        while (m_state == ThreadState::PAUSED || m_state == ThreadState::IDLE)
        {
            m_state_changed.wait(lock);
        }
        while (m_state == ThreadState::RUNNING && m_job != nullptr && m_job->run())
        {
            ;
        }

    } while (m_state != ThreadState::ABORTED);
    m_task_func = nullptr;
}

