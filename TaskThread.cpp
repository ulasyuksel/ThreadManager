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

ThreadState TaskThread::status()
{
    return m_state;
}

void TaskThread::setTask(std::function<bool()> task_func)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_task_func = move(task_func);
}

void TaskThread::internalTask() {
    std::unique_lock<std::mutex> lock(m_mutex);
    do
    {
        while (m_state == ThreadState::PAUSED || m_state == ThreadState::IDLE)
        {
            m_state_changed.wait(lock);
        }
        while (m_state == ThreadState::RUNNING && m_task_func != nullptr && m_task_func())
        {
            ;
        }

    } while (m_state != ThreadState::ABORTED);
    m_task_func = nullptr;
}

