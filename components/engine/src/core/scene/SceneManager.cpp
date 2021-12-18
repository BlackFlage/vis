//
// Created by BlackFlage on 16.12.2021.
//

#include "SceneManager.h"

#include <algorithm>

namespace vis
{

    vis::SceneManager::SceneManager()
    {
        m_current_scene = load_scene("default.scene");
    }

    SceneManager::~SceneManager()
    {
        std::for_each(m_scenes.begin(), m_scenes.end(), std::default_delete<Scene>());
    }

    void SceneManager::change_scene(const std::string& a_name)
    {

    }

    Scene* SceneManager::load_scene(const std::string &a_name)
    {
        Scene* scene = new Scene();

        m_scenes.push_back(scene);

        return scene;
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

    Scene *SceneManager::get_current_scene() const
    {
        return m_current_scene;
    }
}