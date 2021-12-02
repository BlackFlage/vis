//
// Created by BlackFlage on 15.11.2021.
//

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include <glm/glm.hpp>

namespace vis
{
    enum class Direction
    {
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        UP,
        DOWN
    };

    class Camera
    {
    public:
        Camera();
        Camera(glm::vec3 a_position);

        void translate(const glm::vec3& a_translation);
        void move(const Direction& a_direction, float a_delta_time);
        void recalculate_perspective(unsigned int a_width, unsigned int a_height);
        void recalculate_direction_vector(float m_x_offset, float m_y_offset);

        void set_speed(float a_speed);

        glm::vec3 get_position() const;
        glm::mat4 get_projection() const;
        glm::mat4 get_view() const;
    private:
        void recalculate_view_matrix();
    private:
        glm::mat4 m_projection;
        glm::mat4 m_view;

        glm::vec3 m_front;
        glm::vec3 m_up;

        glm::vec3 m_position;

        float m_sensitivity;
        float m_yaw;
        float m_pitch;
        float m_speed;
    };
}


#endif //MAIN_CAMERA_H
