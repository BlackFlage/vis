#include "Shader.h"
#include "Window.h"
#include "Application.h"
#include "Sandbox.h"

int main()
{
    auto app = vis::Application::create_instance();

    app->initialize();
    vis::Shader s("C:\\Users\\BlackFlage\\vertex.glsl", "C:\\Users\\BlackFlage\\fragment.glsl");

    vis::Layer* sandbox = new vis::Sandbox();
    app->push_layer(sandbox);

    app->run();

    delete app;

    return 0;
}
