//
// Created by BlackFlage on 13.02.2022.
//

#include <filesystem>
#include <fstream>

#include "ResourcesManager.h"
#include "MeshManager.h"
#include "TPool.h"

#define DEFAULT_MESHES_FILE_PATH "config/default_meshes.txt"

namespace vis
{
    ResourcesManager* ResourcesManager::m_instance = nullptr;

    ResourcesManager* ResourcesManager::get()
    {
        if(m_instance == nullptr)
        {
            LOG_INFO("Creating ResourcesManager");
            m_instance = new ResourcesManager();
        }

        return m_instance;
    }

    bool ResourcesManager::start_up()
    {
        m_dependencies.push_back(MeshManager::get());

        if(!Manager::start_up())
        {
            LOG_ERROR("Failed to start up dependencies of ResourcesManager");
            return false;
        }

        std::ifstream default_meshes_file(DEFAULT_MESHES_FILE_PATH);

        std::string current_path;
        if(default_meshes_file.is_open())
        {
            while(std::getline(default_meshes_file, current_path))
            {
                m_default_meshes.push_back(current_path);
            }

            load_default_meshes();
        }
        else
        {
            LOG_WARNING("Failed to open default meshes config file: {0}",  DEFAULT_MESHES_FILE_PATH);
        }

        return true;
    }

    bool ResourcesManager::shut_down()
    {
        bool ret_val;
        if(!(ret_val = Manager::shut_down()))
        {
            LOG_ERROR("Failed to shut down dependencies of ResourcesManager");
        }

        return ret_val;
    }

    void ResourcesManager::load_meshes_in_folders(const std::filesystem::path& a_path)
    {
        if(std::filesystem::exists(a_path))
        {
            auto mesh_manager = MeshManager::get();
            for(auto& dir : std::filesystem::directory_iterator(a_path))
            {
                if(std::filesystem::is_directory(dir))
                {
                    load_meshes_in_folders(dir.path());
                }
                else
                {
                    TPool::get_instance()->add_job([mesh_manager, p = dir.path().string()] { mesh_manager->load_mesh(p); });
                }
            }
        }
        else
        {
            LOG_WARNING("Folder doesn't exist: {0}", a_path.string().c_str());
        }
    }

    void ResourcesManager::load_default_meshes()
    {
        auto mesh_manager = MeshManager::get();
        for(const auto& path : m_default_meshes)
        {
            TPool::get_instance()->add_job([mesh_manager, p = path] { mesh_manager->load_mesh(p); });
        }
    }
}