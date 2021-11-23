//
// Created by BlackFlage on 13.11.2021.
//

#ifndef MAIN_MODEL_H
#define MAIN_MODEL_H

#include <vector>
#include <GL/glew.h>
#include <vector>
#include <string>
#include "Mesh.h"
#include "OBJLoader.h"
#include "Texture.h"

namespace vis
{
    class Model
    {
    public:
        Model(const std::vector<std::string>& a_model_paths, const std::string& a_texture_path);
        Model(const std::vector<std::string>& a_file_paths, glm::vec3 a_position);
        ~Model();

        const std::vector<Mesh*>& get_meshes() const;

        const glm::mat4& get_transform() const;

        void bind_texture() const;
        void unbind_texture() const;
    private:
        void load_meshes(const std::vector<std::string>& a_file_paths);
    private:
        std::vector<Mesh*> m_meshes;
        Texture* m_texture;

        glm::vec3 m_position;
    };
}

#endif //MAIN_MODEL_H
