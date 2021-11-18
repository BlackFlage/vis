//
// Created by BlackFlage on 15.11.2021.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Application.h"

namespace vis
{
    Camera::Camera()
    {
        RECT client_area = Application::get_window_instance()->get_client_rect();

        LOG_INFO("RIGHT: {0}", client_area.right);
        LOG_INFO("BOTTOM: {0}", client_area.bottom);

        m_projection = glm::perspective(glm::radians(45.0f), 720.0f / 710.0f, 0.1f, 100.0f);
        m_position = glm::vec3(0.0f);
        m_rotation = glm::vec3(0.0f);
        m_scale = glm::vec3(1.0f);
    }

    Camera::Camera(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale)
    {
        RECT client_area = Application::get_window_instance()->get_client_rect();

        m_projection = glm::perspective(glm::radians(45.0f), (float)client_area.right / (float)client_area.bottom, 0.1f, 100.0f);
        m_position = a_position;
        m_rotation = a_rotation;
        m_scale = a_scale;
    }

    glm::mat4 Camera::get_transform() const
    {
        glm::mat4 transform = m_projection;
        transform = glm::translate(transform, m_position);

        transform = glm::rotate(transform, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        transform = glm::scale(transform, m_scale);

        return transform;
    }

    void Camera::translate(const glm::vec3 &a_translation)
    {
        m_position += a_translation;
    }

    void Camera::recalculate_perspective(unsigned int a_width, unsigned int a_height)
    {
        m_projection = glm::perspective(glm::radians(45.0f), (float)a_width / (float)a_height, 0.1f, 100.0f);
    }
}