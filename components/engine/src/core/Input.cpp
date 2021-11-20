//
// Created by BlackFlage on 18.11.2021.
//

#include "Input.h"

namespace vis
{
    Input::Input()
    {
        m_mouse_pos_x = 0.0f;
        m_mouse_pos_y = 0.0f;
        m_mouse_delta_x = 0.0f;
        m_mouse_delta_y = 0.0f;
    }

    std::pair<float, float> Input::get_mouse_pos() const
    {
        return std::make_pair(m_mouse_pos_x, m_mouse_pos_y);
    }

    float Input::get_mouse_pos_x() const
    {
        return m_mouse_pos_y;
    }

    float Input::get_mouse_pos_y() const
    {
        return m_mouse_pos_x;
    }

    void Input::add_mouse_pos(float a_pos_x, float a_pos_y)
    {
        m_mouse_pos_x += a_pos_x;
        m_mouse_pos_y += a_pos_y;
        m_mouse_delta_x = a_pos_x;
        m_mouse_delta_y = a_pos_y;
    }

    float Input::get_mouse_delta_x() const
    {
        return m_mouse_delta_y;
    }

    float Input::get_mouse_delta_y() const
    {
        return m_mouse_delta_y;
    }
}