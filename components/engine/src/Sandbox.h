//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_SANDBOX_H
#define VISUAL_SANDBOX_H

#include "Layer.h"
#include <iostream>

namespace vis
{
    class Sandbox : public Layer
    {
    public:
        Sandbox() { std::cout << "Layer created!\n"; }
        ~Sandbox() { std::cout << "Layer destroyed!\n"; }

        void on_event(const Event& a_event) override { std::cout << a_event.get_name() << '\n'; }
        void on_update() override {}

        void on_attach() override { std::cout << "Layer attached!\n"; }
        void on_detach() override { std::cout << "Layer detached!\n"; }
    };
}

#endif //VISUAL_SANDBOX_H
