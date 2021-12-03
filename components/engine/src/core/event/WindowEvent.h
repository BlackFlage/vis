//
// Created by BlackFlage on 18.11.2021.
//

#ifndef MAIN_WINDOWEVENT_H
#define MAIN_WINDOWEVENT_H

#include <Windows.h>

#include "Event.h"

namespace vis
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(RECT a_new_client_rect)
        : m_client_width(a_new_client_rect.right), m_client_height(a_new_client_rect.bottom) {}

        inline static EventType get_static_type() { return EventType::WINDOW_RESIZE_EVENT; };
        inline std::string get_name() const override { return "Window resize event."; }
        inline EventType get_event_type() const override { return EventType::WINDOW_RESIZE_EVENT; }

        inline int get_width() const { return m_client_width; }
        inline int get_height() const { return m_client_height; }
    private:
        UINT m_client_width;
        UINT m_client_height;
    };
}

#endif //MAIN_WINDOWEVENT_H
