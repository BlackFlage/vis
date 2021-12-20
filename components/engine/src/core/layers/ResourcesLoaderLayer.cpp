//
// Created by BlackFlage on 20.12.2021.
//

#include "ResourcesLoaderLayer.h"

namespace vis
{
    ResourcesManager* ResourcesManager::m_instance = new ResourcesManager();

    void ResourcesLoaderLayer::on_attach()
    {
        m_resources_manager = ResourcesManager::get_instance();
    }

    void ResourcesLoaderLayer::on_detach()
    {
        delete m_resources_manager;
    }

    void ResourcesLoaderLayer::on_event(Event &a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<KeyPressEvent>([this](auto&& event) { on_key_press_event(std::forward<decltype(event)>(event)); });
    }

    void ResourcesLoaderLayer::on_update(float a_dt)
    {

    }

    void ResourcesLoaderLayer::on_render()
    {

    }

    void ResourcesLoaderLayer::on_imgui_render()
    {

    }

    void ResourcesLoaderLayer::on_key_press_event(KeyPressEvent &a_event)
    {
        if(a_event.get_key_code() == 'C')
        {
            m_resources_manager->load_mesh("C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\models\\default\\cube.obj");
        }
        else if(a_event.get_key_code() == 'S')
        {
            m_resources_manager->load_mesh("C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\models\\default\\sphere.obj");
        }
    }
}