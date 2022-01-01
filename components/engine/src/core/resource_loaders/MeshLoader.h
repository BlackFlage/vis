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

        std::uint16_t            load_mesh(const std::string& a_path);
        std::string              get_name(std::uint16_t a_id);
        int                      get_id(const std::string& a_name);
        void                     delete_mesh(const std::string& a_path);
        void                     load_meshes_in_folders(const std::filesystem::path& a_path);
        Mesh*                    get_mesh(std::uint16_t a_id);
        std::vector<const char*> get_available_meshes();
    private:
        enum class OPERATION_TYPE
        {
            VERTEX,
            TEXTURE,
            NORMAL,
            FACE,
            OTHER
        };

        void load_default_meshes();

        void extract_face_data(std::vector<glm::vec3>& a_destination, std::string& a_line);

        void assign_vertices_and_indices(std::vector<Vertex>& a_vert_dest, std::vector<unsigned int>& a_ind_dest,
                                         std::vector<glm::vec3>& a_vertices, std::vector<glm::vec2>& a_texture_coords,
                                         std::vector<glm::vec3>& a_normals, std::vector<glm::vec3>& a_faces);

        void push_to_vec(std::vector<glm::vec3>& a_destination, float v0, float v1, float v2)
        {
            a_destination.push_back(glm::vec3(v0, v1, v2));
        }

        void push_to_vec(std::vector<glm::vec2>& a_destination, float v0, float v1, float v2)
        {
            a_destination.push_back(glm::vec2(v0, v1));
        }

        template<typename T>
        void parse_line(MeshLoader::OPERATION_TYPE a_type, std::vector<T> &a_destination, std::string &a_line)
        {
            std::stringstream ss(a_line);
            std::vector<float> values;

            float v;
            while(ss >> v)
            {
                values.push_back(v);
            }

            switch(a_type)
            {
                case OPERATION_TYPE::VERTEX:
                case OPERATION_TYPE::NORMAL:
                    if(values.size() == 3)
                    {
                        push_to_vec(a_destination, values.at(0), values.at(1), values.at(2));
                    }
                    break;
                case OPERATION_TYPE::TEXTURE:
                    if(values.size() == 2 || values.size() == 3)
                    {
                        push_to_vec(a_destination, values.at(0), values.at(1), 0);
                    }
                    break;
                default:
                    break;
            }
        }

        OPERATION_TYPE get_operation_type(std::string& a_line);
    private:
        std::unordered_map<std::string, std::uint16_t> m_path_to_index;
        std::unordered_map<std::uint16_t, std::string> m_index_to_name;
        std::unordered_map<std::string, std::uint16_t> m_name_to_index;
        std::unique_ptr<ResourceArray<Mesh>> m_mesh_array;
    };
}

#endif //MAIN_MESHLOADER_H
