//
// Created by BlackFlage on 05.10.2021.
//

#ifndef VISUAL_EVENT_H
#define VISUAL_EVENT_H

namespace vis
{
    enum class EventType
    {
        KEY_PRESS,
        KEY_RELEASE,
        MOUSE_BUTTON_PRESS,
        MOUSE_BUTTON_RELEASE,
        MOUSE_MOVE,
        SCROLL
    };

    class Event
    {
    public:
        virtual std::string get_name() const = 0;
        virtual EventType get_event_type() const = 0;
    };
}


#endif //VISUAL_EVENT_H
