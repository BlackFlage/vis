//
// Created by BlackFlage on 01.10.2021.
//

#include "Application.h"
#include <iostream>

namespace vis
{
    Application* Application::m_instance = nullptr;
    Window* Application::m_window = nullptr;

    Application::Application()
    {
        recalculate_refresh_interval();
        std::cout << "Refersh rate: " << m_refresh_interval;
    }

    Application::~Application()
    {
        m_layer_stack.clear_stack();
    }

    void Application::run()
    {
        std::optional<int> windowRetValue;

        while(windowRetValue != APPLICATION_CLOSED)
        {
            windowRetValue = m_window->pull_events();
            on_update();
        }
    }

    void Application::initialize()
    {
        m_window = vis::Window::create_window(1280, 720, "App");
        m_window->show_window();
        m_window->set_window_callback([this](auto && PH1) { on_event(std::forward<decltype(PH1)>(PH1)); });
    }

    void Application::on_event(const Event &a_event)
    {
        for(const auto& l : m_layer_stack.get_layers())
        {
            l->on_event(a_event);
        }
    }

    void Application::on_update()
    {
        double time_delta = m_timer.get_delta_time();
        while(time_delta > m_refresh_interval) {
            m_window->pull_events();
            m_layer_stack.update_all_layers();

            time_delta -= m_refresh_interval;
            m_timer.new_time_stamp();
        }
    }
}


