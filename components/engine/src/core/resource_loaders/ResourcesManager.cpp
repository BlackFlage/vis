//
// Created by BlackFlage on 20.12.2021.
//

#include "ResourcesManager.h"

namespace vis
{
    std::shared_ptr<ResourcesManager> ResourcesManager::m_instance;

    ResourcesManager::ResourcesManager()
    {
        m_mesh_loader = std::make_unique<MeshLoader>();
    }

    std::shared_ptr<ResourcesManager> ResourcesManager::get_instance()
    {
        return m_instance;
    }

    std::uint16_t ResourcesManager::load_mesh(const std::string& a_name)
    {
        return m_mesh_loader->load_mesh(a_name);
    }

    Mesh *ResourcesManager::get_mesh(std::uint16_t a_id)
    {
        return m_mesh_loader->get_mesh(a_id);
    }

    void ResourcesManager::init()
    {
        m_instance = std::make_shared<ResourcesManager>();
    }

    std::vector<const char*> ResourcesManager::get_available_meshes()
    {
        return m_mesh_loader->get_available_meshes();
    }

    std::string ResourcesManager::get_mesh_name_from_id(int a_id)
    {
        return m_mesh_loader->get_name(a_id);
    }

    int ResourcesManager::get_mesh_id(const std::string &a_name)
    {
        return m_mesh_loader->get_id(a_name);
    }

    void ResourcesManager::load_meshes_in_folders(const std::filesystem::path &a_path)
    {
        m_mesh_loader->load_meshes_in_folders(a_path);
    }
}