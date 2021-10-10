#include "Window.h"
#include "Application.h"
#include "Sandbox.h"

int main()
{
    auto app = vis::Application::create_instance();

    app->initialize();

    vis::Layer* sandbox = new vis::Sandbox();
    app->push_layer(sandbox);

    app->run();

    delete app;

    return 0;
}
