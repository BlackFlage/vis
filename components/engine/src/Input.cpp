//
// Created by BlackFlage on 01.10.2021.
//

#include "Input.h"
#include <Windows.h>

namespace vis
{
    vis::Input vis::Input::m_input;

    bool Input::is_key_pressed(int a_key_code)
    {
        return GetKeyState(a_key_code) & 0x8000;
    }

    bool Input::is_key_held(int a_key_code)
    {
        return false;
    }

    bool Input::is_key_released(int a_key_code)
    {
        return !(GetKeyState(a_key_code) & 0x8000);
    }

    std::pair<int, int> Input::get_mouse_pos()
    {
        return std::make_pair(m_mouse_x_pos, m_mouse_y_pos);
    }

    int Input::get_mouse_x_pos()
    {
        return m_mouse_x_pos;
    }

    int Input::get_mouse_y_pos()
    {
        return m_mouse_y_pos;
    }
}