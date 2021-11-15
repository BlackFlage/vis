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
        ~Model();

        const Mesh* get_mesh() const;
    private:
        Mesh* m_mesh;
    };
}

#endif //MAIN_MODEL_H
