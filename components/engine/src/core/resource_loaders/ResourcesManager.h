//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_RESOURCESMANAGER_H
#define MAIN_RESOURCESMANAGER_H

#include "MeshLoader.h"

namespace vis
{
    class ResourcesManager
    {
    public:
        ResourcesManager();
        ~ResourcesManager() = default;

        static ResourcesManager* get_instance();

        std::uint16_t load_mesh(const std::string& a_name);
        Mesh* get_mesh(std::uint16_t a_id);
    private:
        static ResourcesManager* m_instance;
        std::unique_ptr<MeshLoader> m_mesh_loader;
    };
}

#endif //MAIN_RESOURCESMANAGER_H
