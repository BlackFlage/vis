#include "Window.h"
#include "Application.h"
#include "Sandbox.h"

int main()
{
    auto app = vis::Application::create_instance();

    vis::Layer* layer = new vis::Sandbox();
    app->initialize();
    app->push_layer(layer);
    app->run();

    delete app;

    return 0;
}
