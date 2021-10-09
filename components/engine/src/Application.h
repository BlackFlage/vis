//
// Created by BlackFlage on 01.10.2021.
//
#pragma once
#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "Window.h"
#include <functional>
#include "LayerStack.h"
#include "Timer.h"

namespace vis
{
    class Application
    {
    public:
        ~Application();

        //App run management
        void run();
        void initialize();

        void on_event(const Event& a_event);
        void on_update();

        inline void push_layer(Layer* a_layer) { m_layer_stack.push_layer(a_layer); }
        inline void detach_layer(Layer* a_layer) { m_layer_stack.detach_layer(a_layer); }

        //Other funcs
        inline void recalculate_refresh_interval() { m_refresh_interval = 1.0 / m_refresh_rate; }
        inline void set_refresh_interval(int a_refresh_interval) { if(a_refresh_interval > 24) m_refresh_interval = a_refresh_interval; recalculate_refresh_interval(); }

        inline static Window* get_window_instance() { return m_window; }
        inline static Application* get_instance() { return m_instance; }

        inline static Application* create_instance() { return new Application(); }
    private:
        Application();
    private:
        static Window* m_window;
        static Application* m_instance;

        Timer m_timer;
        LayerStack m_layer_stack;

        double m_refresh_rate = 60.0; //frames per second
        double m_refresh_interval;
    };

    Application* create_instance();
}


#endif //VISUAL_APPLICATION_H
