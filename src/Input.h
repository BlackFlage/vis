//
// Created by BlackFlage on 01.10.2021.
//

#ifndef VISUAL_INPUT_H
#define VISUAL_INPUT_H

#include <utility>

namespace vis
{
    class Input
    {
    public:
        inline static Input get_instance() { return m_input; }

        bool is_key_pressed(int a_key_code);
        bool is_key_held(int a_key_code);
        bool is_key_released(int a_key_code);

        std::pair<int, int> get_mouse_pos();
        int get_mouse_x_pos();
        int get_mouse_y_pos();
    private:
        static Input m_input;

        int m_mouse_x_pos;
        int m_mouse_y_pos;
    };
}


#endif //VISUAL_INPUT_H
