//
// Created by BlackFlage on 09.10.2021.
//

#ifndef MAIN_TIMER_H
#define MAIN_TIMER_H

#include <chrono>

namespace vis
{
    class Timer
    {
    public:
        Timer()
        {
            m_last_stamp = std::chrono::high_resolution_clock::now();
        }

        double get_delta_time()
        {
            auto now = std::chrono::high_resolution_clock::now();

            return double(std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_stamp).count() / 1000.0);
        }

        void new_time_stamp()
        {
            m_last_stamp = std::chrono::high_resolution_clock::now();
        }
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_last_stamp;
    };
}

#endif //MAIN_TIMER_H
