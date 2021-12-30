#include "Window.h"
#include "Application.h"
#include "layers/Sandbox.h"
#include "layers/ImGuiLayer.h"
#include "layers/ResourcesLoaderLayer.h"
#include "layers/SceneEditorLayer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    vis::Application* app = vis::Application::create_instance();

    if(app != nullptr)
    {
        vis::Layer* sandbox = new vis::Sandbox();
        vis::Layer* resources_loader_layer = new vis::ResourcesLoaderLayer();
        vis::Layer* im_gui_layer = new vis::ImGuiLayer();
        vis::Layer* scene_editor_layer = new vis::SceneEditorLayer();

        app->push_layer(im_gui_layer);
        app->push_layer(resources_loader_layer);
        app->push_layer(sandbox);
        app->push_layer(scene_editor_layer);

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
