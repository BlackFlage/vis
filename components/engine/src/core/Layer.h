//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_LAYER_H
#define VISUAL_LAYER_H

#include "event/Event.h"

namespace vis
{
    class Layer
    {
    public:
        virtual ~Layer() = default;;
        virtual void on_attach() = 0;
        virtual void on_detach() = 0;

        virtual void on_event(Event& a_event) = 0;
        virtual void on_update() = 0;
        virtual void on_render() = 0;
    };
}


#endif //VISUAL_LAYER_H
