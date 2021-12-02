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

        m_projection = glm::perspective(glm::radians(45.0f), (float)client_area.right / (float)client_area.bottom, 0.1f, 100.0f);
        m_position = glm::vec3(0.0f);

        m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_up = glm::vec3 (0.0f, 1.0f, 0.0f);

        m_yaw = -90.0f;
        m_pitch = 0.0f;
        m_sensitivity = 0.1f;
        m_speed = 5.0f;

        recalculate_view_matrix();
    }

    Camera::Camera(glm::vec3 a_position)
    {
        RECT client_area = Application::get_window_instance()->get_client_rect();

        m_projection = glm::perspective(glm::radians(45.0f), (float)client_area.right / (float)client_area.bottom, 0.1f, 100.0f);
        m_position = a_position;

        m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_up = glm::vec3 (0.0f, 1.0f, 0.0f);

        m_yaw = -90.0f;
        m_pitch = 0.0f;
        m_sensitivity = 0.1f;
        m_speed = 400.0f;

        recalculate_view_matrix();
    }

    void Camera::translate(const glm::vec3 &a_translation)
    {
        m_position += a_translation;
    }

    void Camera::recalculate_perspective(unsigned int a_width, unsigned int a_height)
    {
        m_projection = glm::perspective(glm::radians(45.0f), (float)a_width / (float)a_height, 0.1f, 100.0f);
    }

    void Camera::recalculate_direction_vector(float m_x_offset, float m_y_offset)
    {
        m_x_offset *= m_sensitivity;
        m_y_offset *= m_sensitivity;

        m_yaw += m_x_offset;
        m_pitch += m_y_offset;

        if(m_pitch > 89.0f)
            m_pitch = 89.0f;
        if(m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_front = glm::normalize(direction);

        recalculate_view_matrix();
    }

    glm::vec3 Camera::get_position() const
    {
        return m_position;
    }

    void Camera::recalculate_view_matrix()
    {
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    }

    glm::mat4 Camera::get_view() const
    {
        return m_view;
    }

    void Camera::move(const Direction& a_direction, float a_delta_time)
    {
        float speed_with_delta = m_speed * a_delta_time;

        if(a_direction == Direction::LEFT)
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * speed_with_delta;
        if(a_direction == Direction::RIGHT)
            m_position += glm::normalize(glm::cross(m_front, m_up)) * speed_with_delta;
        if(a_direction == Direction::FRONT)
            m_position += m_front * speed_with_delta;
        if(a_direction == Direction::BACK)
            m_position -= m_front * speed_with_delta;
        if(a_direction == Direction::UP)
            m_position += m_up * speed_with_delta;
        if(a_direction == Direction::DOWN)
            m_position -= m_up * speed_with_delta;

    }

    glm::mat4 Camera::get_projection() const
    {
        return m_projection;
    }

    void Camera::set_speed(float a_speed)
    {
        if(a_speed < 0.0f || a_speed > 1000.0f)
        {
            LOG_ERROR("Invalid argument! Camera speed must be between 0.0f and 10000.0f!");
            return;
        }

        m_speed = a_speed;
    }
}