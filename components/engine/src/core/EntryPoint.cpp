#include "Window.h"
#include "Application.h"
#include "layers/Sandbox.h"
#include "layers/EntityComponentSystemLayer.h"
#include "layers/ImGuiLayer.h"

int main()
{
    vis::Application* app = vis::Application::create_instance();

    if(app != nullptr)
    {
        vis::Layer* sandbox = new vis::Sandbox();
        vis::Layer* entity_component_system_layer = new vis::EntityComponentSystemLayer();
        vis::Layer* im_gui_layer = new vis::ImGuiLayer();

        app->push_layer(im_gui_layer);
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
