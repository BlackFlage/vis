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
        Input();
        Input(float x_pos, float y_pos);
        ~Input() = default;

        float get_mouse_pos_x() const;
        float get_mouse_pos_y() const;
        float get_mouse_delta_x() const;
        float get_mouse_delta_y() const;

        bool is_mouse_button_clicked(int a_button) const;

        std::pair<float, float> get_mouse_pos() const;

        void set_mouse_pos(float a_pos_x, float a_pos_y);
        void set_button_state(int a_button, bool a_state);
    private:
        float m_mouse_pos_x;
        float m_mouse_pos_y;

        float m_last_mouse_pos_x;
        float m_last_mouse_pos_y;

        bool m_mouse_buttons_state[2];
    };
}


#endif //VISUAL_INPUT_H
