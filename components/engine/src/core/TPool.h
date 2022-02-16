//
// Created by BlackFlage on 06.02.2022.
//

#ifndef MAIN_TPOOL_H
#define MAIN_TPOOL_H

#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <queue>

namespace vis
{
    class TPool
    {
    public:
        ~TPool();

        TPool(const TPool& other) = delete;
        TPool& operator=(const TPool& other) = delete;

        bool add_job(std::function<void()> job);

        static void shutdown();
        static void initialize();
        static TPool* get_instance();
    private:
        TPool();

        void thread_default_function();
    private:
        bool m_threads_available;
        bool m_terminate_pool;
        bool m_stopped;
        std::vector<std::thread> m_threads;
        std::vector<std::thread>::iterator m_current_thread;
        std::queue<std::function<void()>> m_jobs_queue;
        std::mutex m_queue_mutex;
        std::condition_variable m_run_condition;

        static TPool* m_instance;
    };
}


#endif //MAIN_TPOOL_H
