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
            LOG_ERROR("Failed to open file: {0} while loading .obj file!", a_path.c_str());
            return MAX_RESOURCES;
        }

        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textureCoords;
        std::vector<unsigned int> vertexNormalIndices;
        std::vector<unsigned int> textureCoordsIndices;
        std::string line;
        int faces_on_line;
        GLuint geometry_type = GL_TRIANGLES;
        bool found_geometry = false;
        float x, y, z;
        while (std::getline(file, line))
        {
            std::istringstream iss;
            std::string operationType = line.substr(0, 2);

            if(operationType == "v ")
            {
                const char* data = line.c_str();

                sscanf_s(data, "v %f %f %f", &x, &y, &z);
                vertices.emplace_back(x, y, z);
            }
            else if(operationType == "vn")
            {
                const char* data = line.c_str();

                sscanf_s(data, "vn  %f %f %f", &x, &y, &z);
                normals.emplace_back(x, y, z);
            }
            else if(operationType == "vt")
            {
                const char* data = line.c_str();

                sscanf_s(data, "vt %f %f", &x, &y);
                textureCoords.emplace_back(x, y);
            }
            else if(operationType == "f ")
            {
                std::string delimiter = "/";
                std::string data = line;

                size_t end_pos = data.find("\r");
                if(end_pos != std::string::npos)
                {
                    data.erase(end_pos, 2);
                }

                size_t pos = 0;
                faces_on_line = 0;
                while(data.size() > 0)
                {
                    if(!found_geometry)
                    {
                        faces_on_line++;
                    }

                    while(data.at(0) == ' ' || data.at(0) == 'f')
                    {
                        data = data.erase(0, 1);
                    }

                    pos = data.find(' ');
                    std::string face = data.substr(0, pos);

                    if(pos == std::string::npos)
                    {
                        pos = data.size() - 1;
                    }

                    data.erase(0, pos + 1);

                    for(int i = 0; i < 3; i++)
                    {
                        pos = face.find(delimiter);
                        if(pos == 0)
                        {
                            face = face.erase(0, 1);
                            continue;
                        }
                        else if(pos == std::string::npos)
                        {
                            pos = face.size();
                        }

                        unsigned int value = std::stoi(face.substr(0, pos)) - 1;
                        face = face.erase(0, pos + delimiter.length());

                        switch(i)
                        {
                            case 0:
                                indices.push_back(value);
                                break;
                            case 1:
                                textureCoordsIndices.push_back(value);
                                break;
                            case 2:
                                vertexNormalIndices.push_back(value);
                                break;
                            default:
                                break;
                        }
                    }
                }

                if(!found_geometry)
                {
                    found_geometry = true;

                    if(faces_on_line > 3)
                    {
                        geometry_type = GL_QUADS;
                    }
                }
            }
        }

        file.close();
        std::vector<Vertex> outVertices;
        outVertices.reserve(indices.size());

        for(int i = 0; i < indices.size(); i++)
        {
            outVertices.emplace_back(Vertex{ vertices.at(indices.at(i)), normals.at(vertexNormalIndices.at(i)), textureCoords.at(textureCoordsIndices.at(i)) });
        }

        LOG_INFO("Successfully loaded file: {0}.", a_path.c_str());

        Mesh* mesh = new Mesh(outVertices, indices, geometry_type);

        std::string file_name = std::filesystem::path(a_path).filename().string();

        std::uint16_t id = m_mesh_array->add_resource(mesh);
        m_path_to_index.insert({a_path, id});
        m_name_to_index.insert({file_name, id});
        m_index_to_name.insert({id, file_name});

        return id;
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
            LOG_WARNING("Trying to get name of non exisisting mesh, id: {0}", a_id);
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
                            load_mesh(entry.path().string());
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
}