//
// Created by BlackFlage on 10.10.2021.
//

#ifndef MAIN_LOGGER_H
#define MAIN_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "ImGui/imgui.h"

#ifdef LOGGER_ACTIVE
    #define LOG_INFO(...)   vis::Logger::get_instance()->info(__VA_ARGS__); vis::SceneConsole::get_instance()->log_info(__VA_ARGS__)
    #define LOG_WARNING(...) vis::Logger::get_instance()->warn(__VA_ARGS__); vis::SceneConsole::get_instance()->log_warning(__VA_ARGS__)
    #define LOG_ERROR(...) vis::Logger::get_instance()->error(__VA_ARGS__); vis::SceneConsole::get_instance()->log_error(__VA_ARGS__)
    #define LOG_TRACE(...) vis::Logger::get_instance()->trace(__VA_ARGS__); vis::SceneConsole::get_instance()->log_trace(__VA_ARGS__)
    #define LOG_CRITICAL(...) vis::Logger::get_instance()->critical(__VA_ARGS__); vis::SceneConsole::get_instance()->log_critical(__VA_ARGS__)
#else
    #define LOG_INFO(...) {}
    #define LOG_WARNING(...) {}
    #define LOG_ERROR(...) {}
    #define LOG_TRACE(...) {}
    #define LOG_CRITICAL(...) {}
#endif

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

    class SceneConsole
    {
    public:
        enum class LOG_LEVEL
        {
            C_INFO = 0,
            C_WARNING = 1,
            C_ERROR = 2,
            C_TRACE = C_INFO,
            C_CRITICAL = 3
        };

        SceneConsole();
        ~SceneConsole() = default;
        void log_info(const char* a_format, ...);
        void log_warning(const char* a_format, ...);
        void log_error(const char* a_format, ...);
        void log_trace(const char* a_format, ...);
        void log_critical(const char* a_format, ...);
        void clear();
        void draw();

        static bool is_created();
        static void initialize();
        static std::shared_ptr<SceneConsole> get_instance();
    private:
        void log_default(LOG_LEVEL a_level, const std::string& a_msg);
    private:
        static bool m_is_created;
        static std::shared_ptr<SceneConsole> m_instance;
        ImVec4 get_color_from_debug_level(LOG_LEVEL a_level);
        std::vector<std::pair<LOG_LEVEL, std::string>> m_buffer;
    };
}

#endif //MAIN_LOGGER_H
