//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_MESHLOADER_H
#define MAIN_MESHLOADER_H

#include <unordered_map>
#include <cstdint>
#include <memory>

#include "ResourceArray.h"
#include "resource_types/Mesh.h"

namespace vis
{
    class MeshLoader
    {
    public:
        MeshLoader();
        ~MeshLoader() = default;

        std::uint16_t load_mesh(const std::string& a_path);
        void delete_mesh(const char* a_path);
        Mesh* get_mesh(std::uint16_t a_id);
    private:

    private:
        std::unordered_map<std::string, std::uint16_t> m_path_to_index;
        std::unique_ptr<ResourceArray<Mesh>> m_mesh_array;
    };
}

#endif //MAIN_MESHLOADER_H
