//
// Created by BlackFlage on 01.10.2021.
//
#pragma once
#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "Window.h"
#include <functional>
#include "LayerStack.h"

namespace vis
{
    class Application
    {
    public:
        ~Application();

        void run();
        void initialize();

        void on_event(const Event& a_event);
        void on_update() {};

        inline void push_layer(Layer* a_layer) { m_layer_stack.push_layer(a_layer); }
        inline void detach_layer(Layer* a_layer) { m_layer_stack.detach_layer(a_layer); }

        inline static Window* get_window_instance() { return m_window; }
        inline static Application* get_instance() { return m_instance; }

        static Application* create_instance();
    private:
        Application();
    private:
        static Window* m_window;
        static Application* m_instance;

        LayerStack m_layer_stack;
    };

}


#endif //VISUAL_APPLICATION_H
