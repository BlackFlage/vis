//
// Created by BlackFlage on 13.11.2021.
//

#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include "Logger.h"

namespace vis
{

    Mesh *OBJLoader::load_from_file(const std::string &a_file_path)
    {
        std::ifstream file(a_file_path);

        if(!file)
        {
            LOG_ERROR("Failed to open file: {0} while loading .obj file!", a_file_path);
            return nullptr;
        }

        std::vector<Vertex> vertices;
        std::vector<Index> indices;
        std::vector<Normal> normals;
        std::vector<TextureCoords> textureCoords;
        std::string line;
        float x, y, z;
        while (std::getline(file, line))
        {
            LOG_INFO(line);
            std::istringstream iss;
            std::string operationType = line.substr(0, 2);

            if(operationType == "v ")
            {
                const char* data = line.c_str();

                sscanf_s(data, "v %f %f %f", &x, &y, &z);
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                LOG_INFO("VERTEX: {0}, {1}, {2}", x, y, z);
            }
            else if(operationType == "vn")
            {
                const char* data = line.c_str();

                sscanf_s(data, "vn  %f %f %f", &x, &y, &z);
                normals.emplace_back(x, y, z);

                LOG_INFO("VERTEX NORMAL: {0}, {1}, {2}", x, y, z);
            }
            else if(operationType == "vt")
            {
                const char* data = line.c_str();

                sscanf_s(data, "vt %f %f", &x, &y);
                textureCoords.emplace_back(x, y);

                LOG_INFO("VERTEX TEXTURE COORDS: {0}, {1}, {2}", x, y, z);
            }
            else if(operationType == "f ")
            {
                const char* data = line.c_str();
                int i_x, i_y, i_z;
                float t_x, t_y, t_w;
                float n_x, n_y, n_z;

                sscanf_s(data, "f %i//%f %i//%f %i//%f", &i_x, &n_x, &i_y, &n_y, &i_z, &n_z);

                indices.push_back(i_x);
                indices.push_back(i_y);
                indices.push_back(i_z);
                normals.emplace_back(n_x, n_y, n_z);
            }
        }

        return new Mesh(vertices, indices, normals, textureCoords, GL_TRIANGLES);
    }
}