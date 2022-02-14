//
// Created by BlackFlage on 13.02.2022.
//

#ifndef MAIN_RESOURCESMANAGER_H
#define MAIN_RESOURCESMANAGER_H

#include "Manager.h"

namespace vis
{
    class ResourcesManager : public Manager
    {
    public:
        bool   start_up() override;
        bool   shut_down() override;
        static ResourcesManager* get();

        void load_meshes_in_folders(const std::filesystem::path& a_path);
        void load_default_meshes();
    private:
        static ResourcesManager* m_instance;

        std::list<std::string> m_default_meshes;
    };
}

#endif //MAIN_RESOURCESMANAGER_H
