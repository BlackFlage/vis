//
// Created by BlackFlage on 10.10.2021.
//

#include "Logger.h"

namespace vis
{
    std::shared_ptr<spdlog::logger> Logger::m_logger;
    std::shared_ptr<SceneConsole> SceneConsole::m_instance;
    bool SceneConsole::m_is_created = false;

    void Logger::initialize()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_logger = spdlog::stdout_color_mt("VISUAL");
        LOG_INFO("Logger initialized successfully!");
    }

    SceneConsole::SceneConsole()
    {
        m_buffer = {};
    }

    void SceneConsole::initialize()
    {
        m_instance = std::make_shared<SceneConsole>();
        m_is_created = true;
    }

    void SceneConsole::log_info(const std::string &a_msg)
    {
        m_buffer.push_back(std::make_pair(LOG_LEVEL::C_INFO, "INFO-> " + a_msg));
    }

    void SceneConsole::log_warning(const std::string &a_msg)
    {
        m_buffer.push_back(std::make_pair(LOG_LEVEL::C_WARNING, "WARNING-> " + a_msg));
    }

    void SceneConsole::log_error(const std::string &a_msg)
    {
        m_buffer.push_back(std::make_pair(LOG_LEVEL::C_ERROR, "ERROR-> " + a_msg));
    }

    void SceneConsole::log_trace(const std::string &a_msg)
    {
        m_buffer.push_back(std::make_pair(LOG_LEVEL::C_TRACE, "TRACE-> " + a_msg));
    }

    void SceneConsole::log_critical(const std::string &a_msg)
    {
        m_buffer.push_back(std::make_pair(LOG_LEVEL::C_CRITICAL, "CRITICAL-> " + a_msg));
    }

    void SceneConsole::clear()
    {
        m_buffer.clear();
    }

    void SceneConsole::draw()
    {
        ImVec4 text_color;
        for(auto it = m_buffer.begin(); it != m_buffer.end(); it++)
        {
            text_color = get_color_from_debug_level(it->first);

            ImGui::PushStyleColor(ImGuiCol_Text, text_color);
            ImGui::TextUnformatted(it->second.c_str());
            ImGui::PopStyleColor();
        }
    }

    ImVec4 SceneConsole::get_color_from_debug_level(LOG_LEVEL a_level)
    {
        switch(a_level)
        {
            case LOG_LEVEL::C_INFO:
                return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            case LOG_LEVEL::C_WARNING:
                return ImVec4(1.0f, 0.83f, 0.0f, 1.0f);
            case LOG_LEVEL::C_ERROR:
                return ImVec4(1.0f, 0.35f, 0.35f, 1.0f);
            case LOG_LEVEL::C_CRITICAL:
                return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
            default:
                return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    std::shared_ptr<SceneConsole> SceneConsole::get_instance()
    {
        return m_instance;
    }

    bool SceneConsole::is_created()
    {
        return m_is_created;
    }
}