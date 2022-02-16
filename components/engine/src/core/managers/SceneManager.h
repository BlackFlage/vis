//
// Created by BlackFlage on 16.12.2021.
//

#ifndef MAIN_SCENEMANAGER_H
#define MAIN_SCENEMANAGER_H

#include <iostream>
#include <vector>

#include "scene/Scene.h"
#include "Manager.h"

#ifdef _DEBUG
    #define SCENE_PATH "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\scenes\\"
#else
    #define SCENE_PATH "..\..\..\res\scenes"
#endif

namespace vis
{
    class SceneManager : public Manager
    {
    public:
        void change_scene(const std::string& a_name);
        bool save_current_scene();

        Scene* load_scene(const std::string& a_name);
        Scene* get_current_scene() const;
        Scene* get_scene(const std::string& a_name);

        static SceneManager* get();
        bool start_up() override;
        bool shut_down() override;
    private:
        SceneManager() = default;
        ~SceneManager() override = default;
    private:
        Scene* m_current_scene;
        std::vector<Scene*> m_scenes;

        static SceneManager* m_instance;
    };
}

#endif //MAIN_SCENEMANAGER_H
