//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_EVENT_H
#define VISUAL_EVENT_H

#include <iostream>
#include <functional>

namespace vis
{
    enum class EventType
    {
        KEY_PRESS,
        KEY_RELEASE,
        CHAR_INPUT,
        MOUSE_BUTTON_PRESS,
        MOUSE_BUTTON_RELEASE,
        MOUSE_MOVE,
        SCROLL,
        WINDOW_RESIZE_EVENT,
        WINDOW_FOCUS_EVENT
    };

    class Event
    {
    public:
        virtual ~Event() {}
        virtual std::string get_name() const = 0;
        virtual EventType get_event_type() const = 0;
    };

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& a_event)
        : m_event(a_event) {}

        template<typename T>
        bool dispatch(std::function<void(T&)> a_func)
        {
            if(m_event.get_event_type() == T::get_static_type())
            {
                a_func(*(T*)(&m_event));
                return true;
            }

            return false;
        }
    private:
        Event& m_event;
    };
}


#endif //VISUAL_EVENT_H
