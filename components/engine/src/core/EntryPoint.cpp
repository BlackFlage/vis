#include "Shader.h"
#include "Window.h"
#include "Application.h"
#include "Sandbox.h"

int main()
{
    auto app = vis::Application::create_instance();

    vis::Layer* sandbox = new vis::Sandbox();
    app->push_layer(sandbox);

    app->initialize();

    app->run();

    delete app;

    return 0;
}
