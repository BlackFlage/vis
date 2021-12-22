//
// Created by BlackFlage on 10.10.2021.
//

#ifndef MAIN_LOGGER_H
#define MAIN_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "ImGui/imgui.h"

#define FIRST_ARG(FIRST, ...) FIRST

#define LOG_INFO(...) vis::Logger::get_instance()->info(__VA_ARGS__); if(vis::SceneConsole::get_instance()->is_created()){vis::SceneConsole::get_instance()->log_info(FIRST_ARG(__VA_ARGS__));}
#define LOG_WARNING(...) vis::Logger::get_instance()->warn(__VA_ARGS__); if(vis::SceneConsole::get_instance()->is_created()){vis::SceneConsole::get_instance()->log_warning(FIRST_ARG(__VA_ARGS__));}
#define LOG_ERROR(...) vis::Logger::get_instance()->error(__VA_ARGS__); if(vis::SceneConsole::get_instance()->is_created()){vis::SceneConsole::get_instance()->log_error(FIRST_ARG(__VA_ARGS__));}
#define LOG_TRACE(...) vis::Logger::get_instance()->trace(__VA_ARGS__); if(vis::SceneConsole::get_instance()->is_created()){vis::SceneConsole::get_instance()->log_trace(FIRST_ARG(__VA_ARGS__));}
#define LOG_CRITICAL(...) vis::Logger::get_instance()->critical(__VA_ARGS__); if(vis::SceneConsole::get_instance()->is_created()){vis::SceneConsole::get_instance()->log_critical(FIRST_ARG(__VA_ARGS__));}


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
        void log_info(const std::string& a_msg);
        void log_warning(const std::string& a_msg);
        void log_error(const std::string& a_msg);
        void log_trace(const std::string& a_msg);
        void log_critical(const std::string& a_msg);
        void clear();
        void draw();

        static bool is_created();
        static void initialize();
        static std::shared_ptr<SceneConsole> get_instance();
    private:
        static bool m_is_created;
        static std::shared_ptr<SceneConsole> m_instance;
        ImVec4 get_color_from_debug_level(LOG_LEVEL a_level);
        std::vector<std::pair<LOG_LEVEL, std::string>> m_buffer;
    };
}

#endif //MAIN_LOGGER_H
