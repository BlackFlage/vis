//
// Created by BlackFlage on 20.12.2021.
//

#include "ResourcesManager.h"

namespace vis
{
    ResourcesManager::ResourcesManager()
    {
        m_mesh_loader = std::make_unique<MeshLoader>();
    }

    ResourcesManager *ResourcesManager::get_instance()
    {
        return m_instance;
    }

    std::uint16_t ResourcesManager::load_mesh(const char *a_name)
    {
        return m_mesh_loader->load_mesh(a_name);
    }

    Mesh *ResourcesManager::get_mesh(std::uint16_t a_id)
    {
        return m_mesh_loader->get_mesh(a_id);
    }
}