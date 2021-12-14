//
// Created by BlackFlage on 18.11.2021.
//

#include "Input.h"
#include "Logger.h"

namespace vis
{
    Input::Input()
    {
        m_mouse_pos_x = 0.0f;
        m_mouse_pos_y = 0.0f;
        m_last_mouse_pos_x = 0.0f;
        m_last_mouse_pos_y = 0.0f;

        m_mouse_buttons_state[0] = false;
        m_mouse_buttons_state[1] = false;
    }

    Input::Input(float x_pos, float y_pos)
    {
        m_mouse_pos_x = x_pos;
        m_mouse_pos_y = y_pos;
        m_last_mouse_pos_x = x_pos;
        m_last_mouse_pos_y = y_pos;
    }

    std::pair<float, float> Input::get_mouse_pos() const
    {
        return std::make_pair(m_mouse_pos_x, m_mouse_pos_y);
    }

    float Input::get_mouse_pos_x() const
    {
        return m_mouse_pos_x;
    }

    float Input::get_mouse_pos_y() const
    {
        return m_mouse_pos_y;
    }

    void Input::set_mouse_pos(float a_pos_x, float a_pos_y)
    {
        m_last_mouse_pos_x = m_mouse_pos_x;
        m_last_mouse_pos_y = m_mouse_pos_y;
        m_mouse_pos_x = a_pos_x;
        m_mouse_pos_y = a_pos_y;
    }

    float Input::get_mouse_delta_x() const
    {
        return m_mouse_pos_x - m_last_mouse_pos_x;
    }

    float Input::get_mouse_delta_y() const
    {
        return m_mouse_pos_y - m_last_mouse_pos_y;
    }

    bool Input::is_mouse_button_clicked(int a_button) const
    {
        if(a_button < 0 || a_button > 1)
        {
            LOG_ERROR("Invalid argument, button must be between 0 and 1!");
            return false;
        }

        return m_mouse_buttons_state[a_button];
    }

    void Input::set_button_state(int a_button, bool a_state)
    {
        if(a_button < 0 || a_button > 1)
        {
            LOG_ERROR("Invalid argument, button must be between 0 and 1!");
        }

        m_mouse_buttons_state[a_button] = a_state;
    }
}