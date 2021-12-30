//
// Created by BlackFlage on 20.12.2021.
//

#include "MeshLoader.h"

#include <fstream>
#include <string>

#include "Logger.h"
#include "GL/glew.h"
#include "Types.h"

namespace vis
{

    MeshLoader::MeshLoader()
    {
        m_path_to_index = {};
        m_mesh_array = std::make_unique<ResourceArray<Mesh>>();
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
                while(data.size() > 0)
                {
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

        Mesh* mesh = new Mesh(outVertices, indices, GL_TRIANGLES);

        std::uint16_t id = m_mesh_array->add_resource(mesh);
        m_path_to_index.insert({a_path, id});

        return id;
    }

    void MeshLoader::delete_mesh(const char *a_path)
    {
        if(m_path_to_index.find(a_path) == m_path_to_index.end())
        {
            LOG_WARNING("Trying to delete non existing mesh: {0}", a_path);
            return;
        }

        m_mesh_array->delete_resource(m_path_to_index.at(a_path));
        m_path_to_index.erase(a_path);
    }

    Mesh *MeshLoader::get_mesh(std::uint16_t a_id)
    {
        return m_mesh_array->get_resource(a_id);
    }
}