//
// Created by BlackFlage on 20.12.2021.
//

#include "MeshLoader.h"

#include <fstream>
#include <string>
#include <filesystem>

#include "Logger.h"
#include "GL/glew.h"
#include "Types.h"
#include "TPool.h"

namespace vis
{
    MeshLoader::MeshLoader()
    {
        m_path_to_index = {};
        m_mesh_array = std::make_unique<ResourceArray<Mesh>>();
        load_default_meshes();
    }

    std::uint16_t MeshLoader::load_mesh(const std::string& a_path)
    {
        if(m_path_to_index.find(a_path) != m_path_to_index.end())
        {
            return m_path_to_index.at(a_path);
        }

        std::ifstream file(a_path);
        if(!file)
        {
            LOG_ERROR("Failed to open .obj file: {0}", a_path.c_str());
            return MAX_RESOURCES;
        }

        LOG_INFO("Starting to load mesh: {0}", a_path.c_str());
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
        std::string name = std::filesystem::path(a_path).stem().string();

        m_path_to_index.insert({a_path, mesh_id});
        m_name_to_index.insert({name, mesh_id});
        m_index_to_name.insert({mesh_id, name});
        LOG_INFO("Finished loading mesh: {0}", a_path.c_str());

        return mesh_id;
    }

    void MeshLoader::delete_mesh(const std::string& a_path)
    {
        if(m_path_to_index.find(a_path) == m_path_to_index.end())
        {
            LOG_WARNING("Trying to delete non existing mesh: {0}", a_path.c_str());
            return;
        }

        m_mesh_array->delete_resource(m_path_to_index.at(a_path));
        m_name_to_index.erase(m_index_to_name.at(m_path_to_index.at(a_path)));
        m_index_to_name.erase(m_path_to_index.at(a_path));
        m_path_to_index.erase(a_path);
    }

    Mesh *MeshLoader::get_mesh(std::uint16_t a_id)
    {
        return m_mesh_array->get_resource(a_id);
    }

    std::string MeshLoader::get_name(std::uint16_t a_id)
    {
        if(m_index_to_name.find(a_id) == m_index_to_name.end())
        {
            LOG_WARNING("Trying to get name of non existing mesh, id: {0}", a_id);
            return "";
        }

        return m_index_to_name.at(a_id);
    }

    std::vector<const char*> MeshLoader::get_available_meshes()
    {
        std::vector<const char*> out;
        for(const auto& pair : m_index_to_name)
        {
            out.push_back(pair.second.c_str());
        }

        return out;
    }

    void MeshLoader::load_default_meshes()
    {
        load_mesh("..\\engine_assets\\meshes\\cube.obj");
        load_mesh("..\\engine_assets\\meshes\\sphere.obj");
    }

    int MeshLoader::get_id(const std::string &a_name)
    {
        if(m_name_to_index.find(a_name) == m_name_to_index.end())
        {
            LOG_WARNING("Trying to get name of non exisisting mesh, id: {0}", a_name.c_str());
            return -1;
        }

        return m_name_to_index.at(a_name);
    }

    void MeshLoader::load_meshes_in_folders(const std::filesystem::path& a_path)
    {
        if(!a_path.empty())
        {
            try
            {
                for(const auto& entry : std::filesystem::directory_iterator(a_path))
                {
                    if(std::filesystem::is_regular_file(entry.path()))
                    {
                        if(entry.path().extension() == ".obj")
                        {
                            TPool::get_instance()->add_job(std::bind(&MeshLoader::load_mesh, this, entry.path().string()));
                        }
                    }
                    else if(std::filesystem::is_directory(entry))
                    {
                        load_meshes_in_folders(entry);
                    }
                }
            }
            catch(std::exception& a_exception)
            {
                LOG_ERROR("Error loading files from folder: {0}", a_exception.what());
            }
        }
    }

    MeshLoader::OPERATION_TYPE MeshLoader::get_operation_type(std::string &a_line)
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

    void MeshLoader::extract_face_data(std::vector<glm::vec3>& a_destination, std::string& a_line)
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

    void MeshLoader::assign_vertices_and_indices(std::vector<Vertex>& a_vert_dest, std::vector<unsigned int>& a_ind_dest,
                                                 std::vector<glm::vec3>& a_vertices, std::vector<glm::vec2>& a_texture_coords,
                                                 std::vector<glm::vec3>& a_normals, std::vector<glm::vec3>& a_faces)
    {
        int texture_coord_ind;
        int normal_ind;
        std::vector<Vertex> out_vertices;
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
}