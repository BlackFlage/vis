//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_LAYER_H
#define VISUAL_LAYER_H

#include "Event.h"

namespace vis
{
    class Layer
    {
    public:
        virtual ~Layer() {};
        virtual void on_attach() = 0;
        virtual void on_detach() = 0;

        virtual void on_event(const Event& a_event) = 0;
        virtual void on_update() = 0;
    };
}


#endif //VISUAL_LAYER_H
