//
// Created by BlackFlage on 13.02.2022.
//

#include <vector>
#include <fstream>
#include <filesystem>

#include "MeshManager.h"
#include "Types.h"
#include "GL/glew.h"

namespace vis
{
    MeshManager* MeshManager::m_instance = nullptr;

    MeshManager *MeshManager::get()
    {
        if(m_instance == nullptr)
        {
            m_instance = new MeshManager();
        }

        return m_instance;
    }

    bool MeshManager::start_up()
    {
        if(!Manager::start_up())
        {
            return false;
        }

        m_mesh_array = std::make_unique<ResourceArray<Mesh>>();

        return true;
    }

    bool MeshManager::shut_down()
    {
        return Manager::shut_down();
    }

    std::uint16_t MeshManager::load_mesh(const std::string &path)
    {
        if(m_path_to_index.find(path) != m_path_to_index.end())
        {
            return m_path_to_index.at(path);
        }

        std::ifstream file(path);
        if(!file)
        {
            LOG_ERROR("Failed to open .obj file: {0}", path.c_str());
            return MAX_RESOURCES;
        }

        LOG_INFO("Starting to load mesh: {0}", path.c_str());
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texture_coords;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> faces;
        std::string current_line;
        while((std::getline(file, current_line)))
        {
            OPERATION_TYPE operation = get_operation_type(current_line);

            switch(operation)
            {
                case OPERATION_TYPE::VERTEX:
                    parse_line<glm::vec3>(OPERATION_TYPE::VERTEX, vertices, current_line);
                    break;
                case OPERATION_TYPE::TEXTURE:
                    parse_line<glm::vec2>(OPERATION_TYPE::TEXTURE, texture_coords, current_line);
                    break;
                case OPERATION_TYPE::NORMAL:
                    parse_line<glm::vec3>(OPERATION_TYPE::NORMAL, normals, current_line);
                    break;
                case OPERATION_TYPE::FACE:
                    extract_face_data(faces, current_line);
                    break;
                default:
                    break;
            }
        }

        file.close();

        std::vector<Vertex> indexed_vertices;
        std::vector<unsigned int> indices;
        assign_vertices_and_indices(indexed_vertices, indices, vertices, texture_coords, normals, faces);

        Mesh* mesh = new Mesh(indexed_vertices, indices, GL_TRIANGLES);
        std::uint16_t mesh_id = m_mesh_array->add_resource(mesh);
        std::string name = std::filesystem::path(path).stem().string();

        m_path_to_index.insert({path, mesh_id});
        m_name_to_index.insert({name, mesh_id});
        m_index_to_name.insert({mesh_id, name});
        LOG_INFO("Finished loading mesh: {0}", path.c_str());

        return mesh_id;
    }

    Mesh *MeshManager::get_mesh(std::uint16_t id)
    {
        return m_mesh_array->get_resource(id);
    }

    std::string MeshManager::get_name(std::uint16_t id)
    {
        if(m_index_to_name.find(id) == m_index_to_name.end())
        {
            LOG_WARNING("Trying to get name of non existing mesh, id: {0}", id);
            return "";
        }

        return m_index_to_name.at(id);
    }

    int MeshManager::get_id(const std::string &name)
    {
        if(m_name_to_index.find(name) == m_name_to_index.end())
        {
            LOG_WARNING("Trying to get name of non existing mesh, id: {0}", name.c_str());
            return -1;
        }

        return m_name_to_index.at(name);
    }

    void MeshManager::delete_mesh(const std::string& path)
    {
        if(m_path_to_index.find(path) == m_path_to_index.end())
        {
            LOG_WARNING("Trying to delete non existing mesh: {0}", path.c_str());
            return;
        }

        m_mesh_array->delete_resource(m_path_to_index.at(path));
        m_name_to_index.erase(m_index_to_name.at(m_path_to_index.at(path)));
        m_index_to_name.erase(m_path_to_index.at(path));
        m_path_to_index.erase(path);
    }

    std::vector<const char *> MeshManager::get_all_meshes_names()
    {
        std::vector<const char*> out;
        for(const auto& pair : m_index_to_name)
        {
            out.push_back(pair.second.c_str());
        }

        return out;
    }

    void MeshManager::extract_face_data(std::vector<glm::vec3> &a_destination, std::string &a_line)
    {
        std::stringstream line_ss(a_line);

        std::vector<int> indices;
        std::string face;
        while(line_ss >> face)
        {
            while(!face.empty())
            {
                try
                {
                    size_t pos = face.find_first_of('/');
                    if(pos == std::string::npos)
                        pos = face.size();

                    if(pos == 0)
                    {
                        indices.push_back(0);
                        face.erase(0, 1);
                    }
                    else
                    {
                        indices.push_back(std::stoi(face.substr(0, pos)));
                        face.erase(0, pos + 1);
                    }
                }
                catch(std::exception& e)
                {
                    indices.push_back(0);
                }
            }

            while(indices.size() < 3)
            {
                indices.push_back(0);
            }
            a_destination.push_back(glm::vec3(indices.at(0) - 1, indices.at(1) - 1, indices.at(2) - 1));
            indices.clear();
        }
    }

    void MeshManager::assign_vertices_and_indices(std::vector<Vertex> &a_vert_dest, std::vector<unsigned int> &a_ind_dest,
                                             std::vector<glm::vec3> &a_vertices,
                                             std::vector<glm::vec2> &a_texture_coords,
                                             std::vector<glm::vec3> &a_normals, std::vector<glm::vec3> &a_faces)
    {
        int texture_coord_ind;
        int normal_ind;
        for(const auto& face : a_faces)
        {
            Vertex v;

            v.m_position = a_vertices.at(face.x);

            texture_coord_ind = face.y;
            normal_ind = face.z;

            if(texture_coord_ind == -1)
                v.m_textureCoords = glm::vec2(0.0f, 0.0f);
            else
                v.m_textureCoords = a_texture_coords.at(texture_coord_ind);

            if(normal_ind == -1)
                v.m_normals = glm::vec3(0.0f, 0.0f, 0.0f);
            else
                v.m_normals = a_normals.at(normal_ind);

            a_vert_dest.push_back(v);
            a_ind_dest.push_back(face.x);
        }
    }

    void MeshManager::push_to_vec(std::vector<glm::vec3>& a_destination, float v0, float v1, float v2)
    {
        a_destination.push_back(glm::vec3(v0, v1, v2));
    }

    void MeshManager::push_to_vec(std::vector<glm::vec2>& a_destination, float v0, float v1, float v2)
    {
        a_destination.push_back(glm::vec2(v0, v1));
    }

    MeshManager::OPERATION_TYPE MeshManager::get_operation_type(std::string &a_line)
    {
        if(!a_line.empty())
        {
            auto pos_it = a_line.find(' ');

            if(pos_it == std::string::npos)
                return OPERATION_TYPE::OTHER;

            std::string prefix = a_line.substr(0, pos_it);
            a_line.erase(0, pos_it + 1);

            if(prefix == "v")
                return OPERATION_TYPE::VERTEX;
            else if(prefix == "vt")
                return OPERATION_TYPE::TEXTURE;
            else if(prefix == "vn")
                return OPERATION_TYPE::NORMAL;
            else if(prefix == "f")
                return OPERATION_TYPE::FACE;
            else
                return OPERATION_TYPE::OTHER;
        }
        else
        {
            return OPERATION_TYPE::OTHER;
        }
    }
}