//
// Created by BlackFlage on 13.11.2021.
//

#ifndef MAIN_MODEL_H
#define MAIN_MODEL_H

#include <vector>
#include <gl/glew.h>
#include "Mesh.h"

namespace vis
{
    class Model
    {
    public:
        Model() = default;
        Model(Mesh* a_mesh);
        Model(Mesh* a_mesh, glm::vec3 a_position);
        ~Model();

        const Mesh* get_mesh() const;

        const glm::mat4& get_transform() const;
    private:
        Mesh* m_mesh;

        glm::vec3 m_position;
    };
}

#endif //MAIN_MODEL_H
