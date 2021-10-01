//
// Created by BlackFlage on 01.10.2021.
//

#include "Application.h"

namespace vis
{
    vis::Application::Application()
        : window(nullptr)
    {

    }

    Application::~Application()
    {
        delete window;
    }

    void Application::run()
    {
        std::optional<int> windowRetValue;

        while(windowRetValue != WM_QUIT)
        {
            windowRetValue = window->pull_events();
        }
    }

    void Application::initialize()
    {
        window = vis::Window::create_window(1280, 720, "App");
        window->show_window();
    }
}


