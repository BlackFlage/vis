//
// Created by BlackFlage on 01.10.2021.
//

#ifndef VISUAL_INPUT_H
#define VISUAL_INPUT_H

#include <utility>
#include <cstdint>
#include <windows.h>

namespace vis
{
    class Input
    {
    public:
        Input();
        Input(std::int16_t x_pos, std::int16_t y_pos);
        ~Input() = default;

        std::int16_t get_mouse_pos_x() const;
        std::int16_t get_mouse_pos_y() const;
        std::int16_t get_mouse_delta_x() const;
        std::int16_t get_mouse_delta_y() const;
        std::int16_t get_last_pos_x() const;
        std::int16_t get_last_pos_y() const;

        bool is_mouse_button_clicked(int a_button) const;

        std::pair<std::int16_t, std::int16_t> get_mouse_pos() const;

        void set_mouse_pos(std::int16_t a_pos_x, std::int16_t a_pos_y);
        void set_button_state(int a_button, bool a_state);

        void reset_states();
    private:
        std::int16_t m_mouse_pos_x;
        std::int16_t m_mouse_pos_y;

        std::int16_t m_last_mouse_pos_x;
        std::int16_t m_last_mouse_pos_y;

        bool m_mouse_buttons_state[2];
    };
}


#endif //VISUAL_INPUT_H
