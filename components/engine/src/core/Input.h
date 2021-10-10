//
// Created by BlackFlage on 01.10.2021.
//

#ifndef VISUAL_INPUT_H
#define VISUAL_INPUT_H

#include <utility>
#include <windows.h>

namespace vis
{
    class Input
    {
    public:
        static bool is_key_pressed(int a_key_code)
        {
            return GetKeyState(a_key_code) & 0x0080;
        }

        static std::pair<int, int> get_mouse_pos()
        {
            POINT pos;
            GetCursorPos(&pos);

            return std::make_pair(pos.x, pos.y);
        }

        static int get_mouse_x_pos()
        {
            return get_mouse_pos().first;
        }

        static int get_mouse_y_pos()
        {
            return get_mouse_pos().second;
        }
    };
}


#endif //VISUAL_INPUT_H
