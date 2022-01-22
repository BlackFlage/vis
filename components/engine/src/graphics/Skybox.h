//
// Created by BlackFlage on 03.01.2022.
//

#ifndef MAIN_SKYBOXC_H
#define MAIN_SKYBOXC_H

#include <vector>
#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"

namespace vis
{
    class Skybox
    {
    public:
        Skybox(const std::vector<std::string>& a_texture_paths);
        ~Skybox();
        Skybox(const Skybox& rhs)            = delete;
        Skybox& operator=(const Skybox& rhs) = delete;

        const std::vector<float>& get_vertices() const;

        void bind() const;
        void unbind() const;
    private:
        GLuint m_id;
        std::vector<float> m_vertices;
    };

}

#endif //MAIN_SKYBOXC_H
