//
// Created by BlackFlage on 10.10.2021.
//

#include "Logger.h"

namespace vis
{
    std::shared_ptr<spdlog::logger> Logger::m_logger;


    void Logger::initialize()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_logger = spdlog::stdout_color_mt("VISUAL");
        LOG_INFO("Logger initialized successfully!");
    }
}