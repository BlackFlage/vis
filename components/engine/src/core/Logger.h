//
// Created by BlackFlage on 10.10.2021.
//

#ifndef MAIN_LOGGER_H
#define MAIN_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define LOG_INFO(...) vis::Logger::get_instance()->info(__VA_ARGS__)
#define LOG_WARNING(...) vis::Logger::get_instance()->warning(__VA_ARGS__)
#define LOG_ERROR(...) vis::Logger::get_instance()->error(__VA_ARGS__)
#define LOG_TRACE(...) vis::Logger::get_instance()->trace(__VA_ARGS__)
#define LOG_CRITICAL(...) vis::Logger::get_instance()->critical(__VA_ARGS__)

namespace vis
{
    class Logger
    {
    public:
        static void initialize();

        static inline std::shared_ptr<spdlog::logger> get_instance() { return m_logger; }
    private:
        static std::shared_ptr<spdlog::logger> m_logger;
    };
}

#endif //MAIN_LOGGER_H
