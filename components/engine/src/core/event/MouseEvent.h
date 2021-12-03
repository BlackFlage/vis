//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_MOUSEEVENT_H
#define VISUAL_MOUSEEVENT_H

#include <string>

#include "Event.h"
#include "utility"

namespace vis
{
    class MouseEvent : public Event
    {
    public:
        MouseEvent(int a_x_offset, int a_y_offset)
        : m_x_offset(a_x_offset), m_y_offset(a_y_offset) {}

        inline int get_x_offset() const { return m_x_offset; }
        inline int get_y_offset() const { return m_y_offset; }
        inline std::pair<int, int> get_pos() { return std::make_pair(m_x_offset, m_y_offset); }
    protected:
        int m_x_offset;
        int m_y_offset;
    };

    class MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(int a_button, int a_x_offset, int a_y_offset)
        : MouseEvent(a_x_offset, a_y_offset), m_button(a_button) {}

        inline int get_button() const { return m_button; }
    protected:
        int m_button;
    };

    class MouseButtonPressEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressEvent(int a_button, int a_x_offset, int a_y_offset)
        : MouseButtonEvent(a_button, a_x_offset, a_y_offset) {}

        static EventType get_static_type() { return EventType::MOUSE_BUTTON_PRESS; }
        virtual inline std::string get_name() const override { return "Mouse button press event, button: " + std::to_string(m_button) + " X: " + std::to_string(m_x_offset) + " Y: " + std::to_string(m_y_offset); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_BUTTON_PRESS; }
    };

    class MouseButtonReleaseEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleaseEvent(int a_button, int a_x_offset, int a_y_offset)
                : MouseButtonEvent(a_button, a_x_offset, a_y_offset) {}

        static EventType get_static_type() { return EventType::MOUSE_BUTTON_RELEASE; }
        virtual inline std::string get_name() const override { return "Mouse button release event, button: " + std::to_string(m_button) + " X: " + std::to_string(m_x_offset) + " Y: " + std::to_string(m_y_offset); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_BUTTON_RELEASE; }
    };

    class MouseMoveEvent : public MouseEvent
    {
    public:
        MouseMoveEvent(int a_x_offset, int a_y_offset)
        : MouseEvent(a_x_offset, a_y_offset) {}

        static EventType get_static_type() { return EventType::MOUSE_MOVE; }
        virtual inline std::string get_name() const override { return "Mouse move event, X: " + std::to_string(m_x_offset) + " Y: " + std::to_string(m_y_offset); }
        virtual inline EventType get_event_type() const override { return EventType::MOUSE_MOVE; }
    };

    class MouseScrollEvent : public MouseEvent
    {
    public:
        MouseScrollEvent(int a_offset, int a_x_offset, int a_y_offset)
        : MouseEvent(a_x_offset, a_y_offset), m_offset(a_offset) {}

        inline int get_offset() const { return m_offset; };

        static EventType get_static_type() { return EventType::SCROLL; }
        virtual inline std::string get_name() const override { return "Mouse scroll event, offset: " + std::to_string(m_offset) + " X: " + std::to_string(m_x_offset) + " Y: " + std::to_string(m_y_offset); }
        virtual inline EventType get_event_type() const override { return EventType::SCROLL; }
    private:
        int m_offset;
    };
}

#endif //VISUAL_MOUSEEVENT_H
