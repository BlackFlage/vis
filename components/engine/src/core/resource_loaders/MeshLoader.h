//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_MESHLOADER_H
#define MAIN_MESHLOADER_H

#include <unordered_map>
#include <cstdint>
#include <memory>
#include <filesystem>

#include "ResourceArray.h"
#include "resource_types/Mesh.h"

namespace vis
{
    class MeshLoader
    {
    public:
        MeshLoader();
        ~MeshLoader() = default;

        std::uint16_t       load_mesh(const std::string& a_path);
        std::string         get_name(std::uint16_t a_id);
        int                 get_id(const std::string& a_name);
        void                delete_mesh(const std::string& a_path);
        void                load_meshes_in_folders(const std::filesystem::path& a_path);
        Mesh*               get_mesh(std::uint16_t a_id);
        std::vector<const char*> get_available_meshes();
    private:
        void load_default_meshes();
    private:
        std::unordered_map<std::string, std::uint16_t> m_path_to_index;
        std::unordered_map<std::uint16_t, std::string> m_index_to_name;
        std::unordered_map<std::string, std::uint16_t> m_name_to_index;
        std::unique_ptr<ResourceArray<Mesh>> m_mesh_array;
    };
}

#endif //MAIN_MESHLOADER_H
