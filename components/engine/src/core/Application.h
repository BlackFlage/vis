//
// Created by BlackFlage on 01.10.2021.
//
#pragma once
#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include <memory>
#include <iostream>
#include <functional>

#include "Window.h"
#include "layers/LayerStack.h"
#include "Timer.h"
#include "event/Event.h"
#include "event/KeyboardEvent.h"
#include "event/WindowEvent.h"
#include "event/MouseEvent.h"
#include "Shader.h"
#include "Input.h"
#include "Framebuffer.h"

#define INPUT Application::get_input_instance()

namespace vis
{
    class Application
    {
    public:
        ~Application();

        void run();
        void initialize();
        void on_event(Event& a_event);
        void on_update();
        void on_render();
        void on_imgui_render();
        void push_layer(Layer* a_layer);
        void detach_layer(Layer* a_layer);
        void recalculate_refresh_interval();
        void set_refresh_interval(int a_refresh_rate);

        inline static Input* get_input_instance() { return m_input; }
        inline static Window* get_window_instance() { return m_window; }
        inline static Application* get_instance() { return m_instance; }
        inline static bool is_running() { return m_running; }
        inline static bool is_minimized() { return m_minimized; }

        inline static void set_minimized(bool minimized) { m_minimized = minimized; }
        inline static void set_running(bool a_running) { m_running = a_running; }
        inline float get_delta_time() { return m_timer.get_delta_time(); }
        inline float get_time_passed() { return m_timer.get_time_passed();}
        inline GLuint get_framebuffer_texture_id() const { return m_scene_framebuffer->get_texture_id(); }

        static Application* create_instance();
        static void paint_custom_caption(HWND m_hwnd, HDC m_hdc);
        static void set_resize_event(WindowResizeEvent* a_event);
    private:
        Application();

        void start_opengl_thread();
        void on_key_press_event(KeyPressEvent& a_event);

        static DWORD WINAPI opengl_thread(LPVOID a_param);
        static void on_resize_event(WindowResizeEvent& a_event);
    private:
        static Window*               m_window;
        static Application*          m_instance;
        static Input*                m_input;
        static WindowResizeEvent*    m_resize_event;
        static bool                  m_running;
        static bool                  m_minimized;
        static bool                  m_opengl_initialized;
        static bool                  m_gl_context_should_resize;
        static bool                  m_layers_attached;

        Timer                        m_timer;
        LayerStack                   m_layer_stack;

        std::unique_ptr<Framebuffer> m_scene_framebuffer;

        double                       m_refresh_rate = 120.0; //frames per second
        double                       m_refresh_interval;
        bool                         m_main_window_open;
    };
}


#endif //VISUAL_APPLICATION_H
