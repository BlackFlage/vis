//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_MOUSEEVENT_H
#define VISUAL_MOUSEEVENT_H

#include "Event.h"
#include "utility"

namespace vis
{
    class MouseEvent : public Event
    {
    public:
        MouseEvent(int a_x_pos, int a_y_pos)
        : m_x_pos(a_x_pos), m_y_pos(a_y_pos) {}

        inline int get_x_pos() const { return m_x_pos; }
        inline int get_y_pos() const { return m_y_pos; }
        inline std::pair<int, int> get_pos() { return std::make_pair(m_x_pos, m_y_pos); }
    protected:
        int m_x_pos;
        int m_y_pos;
    };

    class MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(int a_button, int a_x_pos, int a_y_pos)
        : MouseEvent(a_x_pos, a_y_pos), m_button(a_button) {}

        inline int get_button() const { return m_button; }
    protected:
        int m_button;
    };

    class MouseButtonPressEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressEvent(int a_button, int a_x_pos, int a_y_pos)
        : MouseButtonEvent(a_button, a_x_pos, a_y_pos) {}

        virtual inline std::string get_name() const override { return "Mouse button press event, button: " + std::to_string(m_button) + " X: " + std::to_string(m_x_pos) + " Y: " + std::to_string(m_y_pos); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_BUTTON_PRESS; }
    };

    class MouseButtonReleaseEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleaseEvent(int a_button, int a_x_pos, int a_y_pos)
                : MouseButtonEvent(a_button, a_x_pos, a_y_pos) {}

        virtual inline std::string get_name() const override { return "Mouse button release event, button: " + std::to_string(m_button) + " X: " + std::to_string(m_x_pos) + " Y: " + std::to_string(m_y_pos); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_BUTTON_RELEASE; }
    };

    class MouseMoveEvent : public MouseEvent
    {
    public:
        MouseMoveEvent(int a_x_pos, int a_y_pos)
        : MouseEvent(a_x_pos, a_y_pos) {}

        virtual inline std::string get_name() const override { return "Mouse move event, X: " + std::to_string(m_x_pos) + " Y: " + std::to_string(m_y_pos); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_MOVE; }
    };

    class MouseScrollEvent : public MouseEvent
    {
    public:
        MouseScrollEvent(int a_offset, int a_x_pos, int a_y_pos)
        : MouseEvent(a_x_pos, a_y_pos), m_offset(a_offset) {}

        inline int get_offset() const { return m_offset; };

        virtual inline std::string get_name() const override { return "Mouse scroll event, offset: " + std::to_string(m_offset) + " X: " + std::to_string(m_x_pos) + " Y: " + std::to_string(m_y_pos); }
        virtual inline EventType get_event_type() const override { return EventType::SCROLL; }
    private:
        int m_offset;
    };
}

#endif //VISUAL_MOUSEEVENT_H
