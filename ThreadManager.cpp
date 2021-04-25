/*
 * ThreadManager.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#include "ThreadManager.hpp"
#include "TaskThread.hpp"

ThreadManager::ThreadManager(unsigned int size)
{
    for(unsigned int i = 0; i < size; i++)
    {
        auto ret = std::make_unique<TaskThread>(i);
        m_task_thread_vector.push_back(std::move(ret));
    }
}

ThreadManager::~ThreadManager()
{
    m_task_thread_vector.clear();
}

ThreadState
ThreadManager::status(unsigned int id)
{
    ThreadState state = ThreadState::UNKNOWN;
    if (m_task_thread_vector.size() > id)
    {
        state = m_task_thread_vector[id]->status();
    }
    return state;
}
void
ThreadManager::setTask(unsigned int id, std::function<bool()> task_func)
{
    if (m_task_thread_vector.size() > id)
    {
        m_task_thread_vector[id]->setTask(task_func);
    }
}

unsigned int
ThreadManager::size()
{
    return m_task_thread_vector.size();
}

void
ThreadManager::start(unsigned int id)
{
    if (m_task_thread_vector.size() > id)
    {
        m_task_thread_vector[id]->start();
    }
}

void
ThreadManager::pause(unsigned int id)
{
    if (m_task_thread_vector.size() > id)
    {
        m_task_thread_vector[id]->pause();
    }
}

void
ThreadManager::abort(unsigned int id)
{
    if (m_task_thread_vector.size() > id)
    {
        m_task_thread_vector[id]->abort();
    }
}

void
ThreadManager::resume(unsigned int id)
{
    if (m_task_thread_vector.size() > id)
    {
        m_task_thread_vector[id]->resume();
    }
}
