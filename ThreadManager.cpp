/*
 * ThreadManager.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: ulasy
 */

#include "ThreadManager.hpp"
#include "TaskThread.hpp"
#include <iostream>
#include <sstream>
#include <string>

static bool TASK_1()
{
    std::cout << "TASK_1_RUNNING" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    return true;
}

ThreadManager::ThreadManager(unsigned int size)
{

    for(unsigned int i = 0; i < size; i++)
    {
        auto ret = std::make_unique<TaskThread>(i);
        m_task_thread_vector.push_back(std::move(ret));
        m_task_thread_vector[i]->setTask(TASK_1);
    }

}

ThreadManager::~ThreadManager() {
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
