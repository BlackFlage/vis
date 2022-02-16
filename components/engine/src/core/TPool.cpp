//
// Created by BlackFlage on 06.02.2022.
//

#include "TPool.h"
#include "Logger.h"

namespace vis
{
    TPool* TPool::m_instance = nullptr;

    TPool::TPool()
    {
        unsigned int max_threads = std::thread::hardware_concurrency();
        m_terminate_pool = false;
        m_stopped = false;

        if(max_threads == 0)
        {
            m_threads_available = false;
            return;
        }

        for(unsigned int i = 0; i < max_threads; i++)
        {
            m_threads.push_back(std::thread(&TPool::thread_default_function, this));
        }
    }

    TPool::~TPool()
    {
        if(!m_stopped)
        {
            shutdown();
        }
    }

    void TPool::thread_default_function()
    {
        while(true)
        {
            std::function<void()> job;
            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);

                m_run_condition.wait(lock, [this]() { return !m_jobs_queue.empty() || m_terminate_pool; });

                if(!m_jobs_queue.empty())
                {
                    job = m_jobs_queue.front();
                    m_jobs_queue.pop();
                }
                else
                {
                    job = nullptr;
                }
            }

            if(job)
            {
                job();
            }
            else
            {
                return;
            }
        }
    }

    void TPool::initialize()
    {
        m_instance = new TPool();

        LOG_INFO("Thread pool initialized successfully!");
    }

    TPool *TPool::get_instance()
    {
        return m_instance;
    }

    bool TPool::add_job(std::function<void()> job)
    {
        if(!m_threads_available)
            return false;

        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_jobs_queue.push(job);
        }

        m_run_condition.notify_one();

        return true;
    }

    void TPool::shutdown()
    {
        if(!m_instance)
            return;

        m_instance->m_terminate_pool = true;

        m_instance->m_run_condition.notify_all();

        for(auto& t : m_instance->m_threads)
        {
            t.join();
        }

        m_instance->m_threads.clear();
        m_instance->m_stopped = true;

        delete m_instance;

        m_instance = nullptr;
    }
}