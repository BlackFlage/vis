//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_KEYBOARDEVENT_H
#define VISUAL_KEYBOARDEVENT_H

#include "Event.h"
#include <string>

namespace vis
{
    class KeyEvent : public Event
    {
    public:
        explicit KeyEvent(int a_key_code)
        :   m_key_code(a_key_code) {}

        int get_key_code() const { return m_key_code; }
    protected:
        int m_key_code;
    };

    class KeyPressEvent : public KeyEvent
    {
    public:
        explicit KeyPressEvent(int a_key_code)
        : KeyEvent(a_key_code) {}

        inline static EventType get_static_type() { return EventType::KEY_PRESS; }
        virtual inline std::string get_name() const override { return "KeyPressEvent: " + std::to_string(m_key_code); }
        virtual inline EventType get_event_type() const override { return EventType::KEY_PRESS; }
    };

    class KeyReleaseEvent : public KeyEvent
    {
    public:
        explicit KeyReleaseEvent(int a_key_code)
        : KeyEvent(a_key_code) {}

        inline static EventType get_static_type() { return EventType::KEY_RELEASE; }
        virtual inline std::string get_name() const override { return "KeyReleaseEvent: " + std::to_string(m_key_code); }
        virtual inline EventType get_event_type() const override { return EventType::KEY_RELEASE; }
    };

    class CharInputEvent : public Event
    {
    public:
        explicit CharInputEvent(char a_char)
        : m_char(a_char) {}

        inline char get_char() const { return m_char; }

        inline static EventType get_static_type() { return EventType::CHAR_INPUT; }
        virtual inline std::string get_name() const override { return "CharInputEvent: " + std::to_string(m_char); }
        virtual inline EventType get_event_type() const override { return EventType::CHAR_INPUT; }
    private:
        char m_char;
    };
}

#endif //VISUAL_KEYBOARDEVENT_H
