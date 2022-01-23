#include "Window.h"
#include "Application.h"
#include "layers/ImGuiLayer.h"
#include "layers/SceneEditorLayer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../vendor/stbimage/stb_image.h"

#ifdef WIN32
int main()
{
    vis::Application* app = vis::Application::create_instance();

    if(app != nullptr)
    {
        vis::Layer* im_gui_layer = new vis::ImGuiLayer();
        vis::Layer* scene_editor_layer = new vis::SceneEditorLayer();

        app->push_layer(im_gui_layer);
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
#else
    #error "Visual supports only Windows platform!"
#endif