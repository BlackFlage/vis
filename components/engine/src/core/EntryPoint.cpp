#include "Window.h"
#include "Application.h"
#include "Sandbox.h"

int main()
{
    vis::Application* app = vis::Application::create_instance();
    auto app2 = vis::Application::create_instance();

    if(app != nullptr)
    {
        vis::Layer* sandbox = new vis::Sandbox();
        app->push_layer(sandbox);

        app->initialize();

        app->run();

        delete app;

        return 0;
    }
    else
    {
        return -1;
    }

}
