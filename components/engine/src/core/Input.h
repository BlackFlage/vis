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

        float get_mouse_pos_x() const;
        float get_mouse_pos_y() const;
        float get_mouse_delta_x() const;
        float get_mouse_delta_y() const;

        std::pair<float, float> get_mouse_pos() const;

        void add_mouse_pos(float a_pos_x, float a_pos_y);
    private:
        float m_mouse_pos_x;
        float m_mouse_pos_y;
        float m_mouse_delta_x;
        float m_mouse_delta_y;
    };
}


#endif //VISUAL_INPUT_H
