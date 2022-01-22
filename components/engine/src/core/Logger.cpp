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

        SceneConsole::initialize();

        LOG_INFO("Logger and SceneConsole initialized successfully!");
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

    void SceneConsole::log_info(const char* a_format, ...)
    {
        log_default(LOG_LEVEL::C_INFO, a_format);
    }

    void SceneConsole::log_warning(const char* a_format, ...)
    {
        log_default(LOG_LEVEL::C_WARNING, a_format);
    }

    void SceneConsole::log_error(const char* a_format, ...)
    {
        log_default(LOG_LEVEL::C_ERROR, a_format);
    }

    void SceneConsole::log_trace(const char* a_format, ...)
    {
        log_default(LOG_LEVEL::C_TRACE, a_format);
    }

    void SceneConsole::log_critical(const char* a_format, ...)
    {
        log_default(LOG_LEVEL::C_CRITICAL, a_format);
    }

    void SceneConsole::clear()
    {
        m_buffer.clear();
    }

    void SceneConsole::draw()
    {
        ImVec4 text_color;

        ImGui::BeginChild("Console child", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        for(auto it = m_buffer.begin(); it != m_buffer.end(); it++)
        {
            text_color = get_color_from_debug_level(it->first);

            ImGui::PushStyleColor(ImGuiCol_Text, text_color);
            ImGui::TextUnformatted(it->second.c_str());
            ImGui::PopStyleColor();
        }

        if(ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
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

    void SceneConsole::log_default(LOG_LEVEL a_level, const std::string& a_msg)
    {
        m_buffer.push_back(std::make_pair(a_level, a_msg));
    }
}