//
// Created by BlackFlage on 15.11.2021.
//

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include <glm/glm.hpp>

namespace vis
{
    class Camera
    {
    public:
        Camera();
        Camera(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale);

        void translate(const glm::vec3& a_translation);
        glm::vec3 get_position() { return m_position; }

        glm::mat4 get_transform() const;
    private:
        glm::mat4 m_projection;

        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
    };
}


#endif //MAIN_CAMERA_H
