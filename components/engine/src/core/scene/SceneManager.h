//
// Created by BlackFlage on 16.12.2021.
//

#ifndef MAIN_SCENEMANAGER_H
#define MAIN_SCENEMANAGER_H

#include "Scene.h"

#include <iostream>
#include <vector>

#ifdef _DEBUG
    #define SCENE_PATH "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\scenes\\"
#else
    #define SCENE_PATH "..\..\..\res\scenes"
#endif

namespace vis
{
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        void change_scene(const std::string& a_name);
        Scene* load_scene(const std::string& a_name);
        bool save_current_scene();

        Scene* get_current_scene() const;
        Scene* get_scene(const std::string& a_name);
    private:
        Scene* m_current_scene;
        std::vector<Scene*> m_scenes;
    };
}

#endif //MAIN_SCENEMANAGER_H
