#include "Window.h"
#include "Application.h"
#include "Sandbox.h"
#include "EntityComponentSystemLayer.h"

int main()
{
    vis::Application* app = vis::Application::create_instance();

    if(app != nullptr)
    {
        vis::Layer* sandbox = new vis::Sandbox();
        vis::Layer* entity_component_system_layer = new vis::EntityComponentSystemLayer();

        app->push_layer(entity_component_system_layer);
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
