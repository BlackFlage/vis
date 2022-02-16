//
// Created by BlackFlage on 16.12.2021.
//

#include "SceneManager.h"

#include <algorithm>

namespace vis
{
    SceneManager* SceneManager::m_instance;

    SceneManager *SceneManager::get()
    {
        if(!m_instance)
        {
            LOG_INFO("Creating SceneManager.");
            m_instance = new SceneManager();
        }

        return m_instance;
    }

    bool SceneManager::start_up()
    {
        if(!Manager::start_up())
        {
            LOG_ERROR("Failed to start up dependencies of SceneManager");
            return false;
        }

        m_current_scene = load_scene("default");

        return m_current_scene != nullptr;
    }

    bool SceneManager::shut_down()
    {
        bool ret_val;
        if(!(ret_val = Manager::shut_down()))
        {
            LOG_ERROR("Failed to shut down dependencies of SceneManager");
        }

        if(m_current_scene)
        {
            m_current_scene->on_unload();
            m_current_scene = nullptr;
        }

        for(const auto& s : m_scenes)
        {
            delete s;
        }

        return ret_val;
    }

    Scene *SceneManager::get_current_scene() const
    {
        return m_current_scene;
    }

    void SceneManager::change_scene(const std::string& a_name)
    {
        if(auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [&a_name](const Scene* scene) { return scene->get_name() == a_name; }) != m_scenes.end())
        {
            Scene* to_change = m_scenes.at(it);

            m_current_scene->on_unload();
            m_current_scene = to_change;
            m_current_scene->on_load();
        }
    }

    Scene* SceneManager::load_scene(const std::string &a_name)
    {
        LOG_INFO("Loading scene: {0}", a_name.c_str());

        Scene* scene = new Scene(a_name);

        if(scene)
        {
            scene->on_load();
            m_scenes.push_back(scene);
            return scene;
        }
        else
        {
            LOG_WARNING("Failed to load scene: {0}", a_name.c_str());
            return nullptr;
        }
    }

    bool SceneManager::save_current_scene()
    {
        return true;
    }

    Scene *SceneManager::get_scene(const std::string& a_name)
    {
        auto s = std::find_if(m_scenes.begin(), m_scenes.end(), [&a_name](Scene* scene){ return scene->get_name() == a_name; });

        if(s != m_scenes.end())
        {
            return *s;
        }

        return nullptr;
    }
}