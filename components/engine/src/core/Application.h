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
#include "Event.h"
#include "KeyboardEvent.h"
#include <iostream>

namespace vis
{
    class Application
    {
    public:
        ~Application();

        //App run management
        void run();
        void initialize();

        void on_event(Event& a_event);
        void on_update();

        inline void push_layer(Layer* a_layer) { m_layer_stack.push_layer(a_layer); }
        inline void detach_layer(Layer* a_layer) { m_layer_stack.detach_layer(a_layer); }

        //Other funcs
        inline void recalculate_refresh_interval() { m_refresh_interval = 1.0 / m_refresh_rate; }
        inline void set_refresh_interval(int a_refresh_rate) {
            if(a_refresh_rate > 24) m_refresh_rate = a_refresh_rate;
            recalculate_refresh_interval(); }

        inline static Window* get_window_instance() { return m_window; }
        inline static Application* get_instance() { return m_instance; }
        inline static bool is_running() { return m_running; }

        inline static void set_running(bool a_running) { m_running = a_running; }

        static Application* create_instance();
    private:
        Application();

        void start_opengl_thread();
        static DWORD WINAPI opengl_thread(LPVOID a_param);
    private:
        static Window* m_window;
        static Application* m_instance;
        static bool m_running;

        Timer other;
        Timer m_timer;
        LayerStack m_layer_stack;

        double m_refresh_rate = 60.0; //frames per second
        double m_refresh_interval;
    };
}


#endif //VISUAL_APPLICATION_H
