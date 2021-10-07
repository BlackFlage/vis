//
// Created by BlackFlage on 01.10.2021.
//

#pragma once

#ifndef VISUAL_WINDOW_H
#define VISUAL_WINDOW_H

#include <Windows.h>
#include <optional>
#include <functional>
#include "Event.h"

#define APPLICATION_CLOSED 333

namespace vis
{
    struct Window_Data
    {
        int m_width;
        int m_height;

        HWND m_hwnd;
        std::function<void(Event&)> m_window_callback;
    };

    class Window
    {
    public:
        Window(const Window_Data& a_window_data);
        ~Window();

        static Window* create_window(int a_width, int a_height, const char*  a_name);

        inline int get_width() const { return m_window_data.m_width; }
        inline int get_height() const { return  m_window_data.m_height; }

        inline void set_width(int a_width) {  m_window_data.m_width = a_width; }
        inline void set_height(int a_height) {  m_window_data.m_height = a_height; }

        inline void show_window() const { ShowWindow(m_window_data.m_hwnd, 5); };
        inline void hide_window() const { ShowWindow(m_window_data.m_hwnd,  0); };
        inline void show_fullscreen() const { ShowWindow(m_window_data.m_hwnd, 3); }

        inline void set_window_callback(const std::function<void(Event&)>& a_func) { m_window_data.m_window_callback = a_func; }

        inline static Window_Data& get_window_data()  { return m_window_data; }

        std::optional<int> pull_events();
        void change_title(const char* a_title);
    private:
        static Window_Data m_window_data;
    };
}


#endif //VISUAL_WINDOW_H
