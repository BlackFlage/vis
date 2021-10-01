//
// Created by BlackFlage on 01.10.2021.
//

#ifndef VISUAL_WINDOW_H
#define VISUAL_WINDOW_H

#include <Windows.h>
#include <optional>

namespace vis
{
    class Window
    {
    public:
        Window(int a_width, int a_height, HWND a_hwnd);
        ~Window();

        static Window* create_window(int a_width, int a_height, const char*  a_name);

        inline int get_width() const { return m_width; }
        inline int get_height() const { return m_height; }

        inline void set_width(int a_width) { m_width = a_width; }
        inline void set_height(int a_height) { m_height = a_height; }

        inline void show_window() const { ShowWindow(m_hwnd, 5); };
        inline void show_fullscreen() const { ShowWindow(m_hwnd, 3); }
        inline void hide_window() const { ShowWindow(m_hwnd, 0); };

        std::optional<int> pull_events();
    private:
        int m_width;
        int m_height;

        HWND m_hwnd;
    };
}


#endif //VISUAL_WINDOW_H
