//
// Created by BlackFlage on 01.10.2021.
//
#pragma once
#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "Window.h"
#include <functional>

namespace vis
{
    class Application
    {
    public:
        ~Application();

        void run();
        void initialize();

        void on_event(const Event& a_event);

        inline static Window* get_window_instance() { return m_window; }
        inline static Application* get_instance() { return m_instance; }

        static Application* create_instance();
    private:
        Application();
    private:
        static Window* m_window;
        static Application* m_instance;
    };

}


#endif //VISUAL_APPLICATION_H
