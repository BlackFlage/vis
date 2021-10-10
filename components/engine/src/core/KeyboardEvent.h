//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_KEYBOARDEVENT_H
#define VISUAL_KEYBOARDEVENT_H

#include "Event.h"
#include <string>

namespace vis
{
    class KeyboardEvent : public Event
    {
    public:
        KeyboardEvent(int a_key_code)
        :   m_key_code(a_key_code) {}

        int get_key_code() const { return m_key_code; }
    protected:
        int m_key_code;
    };

    class KeyPressEvent : public KeyboardEvent
    {
    public:
        KeyPressEvent(int a_key_code)
        : KeyboardEvent(a_key_code) {}

        static EventType get_static_type() { return EventType::KEY_PRESS; }
        virtual inline std::string get_name() const override { return "Key press event, key code: " + std::to_string(get_key_code()) + " char: " + char(m_key_code); }
        virtual inline EventType get_event_type() const override { return EventType::KEY_PRESS; }
    };

    class KeyReleaseEvent : public KeyboardEvent
    {
    public:
        KeyReleaseEvent(int a_key_code)
        : KeyboardEvent(a_key_code) {}

        static EventType get_static_type() { return EventType::KEY_RELEASE; }
        virtual inline std::string get_name() const override { return "Key release event, key code: " + std::to_string(get_key_code()) + " char: " + char(m_key_code); }
        virtual inline EventType get_event_type() const override { return EventType::KEY_RELEASE; }
    };
}

#endif //VISUAL_KEYBOARDEVENT_H
