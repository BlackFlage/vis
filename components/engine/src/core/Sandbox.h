//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_SANDBOX_H
#define VISUAL_SANDBOX_H

#include "Layer.h"
#include <iostream>
#include "Input.h"
#include "Gl/gl.h"

namespace vis
{
    class Sandbox : public Layer
    {
    public:
        Sandbox() { std::cout << "Layer created!\n"; }
        ~Sandbox() override { std::cout << "Layer destroyed!\n"; }

        void on_event(const Event& a_event) override { ; }
        void on_update() override {
            if(Input::is_key_pressed('A'))
            {
                glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            }
            else if(Input::is_key_pressed('S'))
            {
                glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            }
            else if(Input::is_key_pressed('D'))
            {
                glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
            }
            else if(Input::is_key_pressed('F'))
            {
                glClearColor(0.5f, 0.3f, 1.0f, 1.0f);
            }
        }

        void on_attach() override { std::cout << "Layer attached!\n"; }
        void on_detach() override { std::cout << "Layer detached!\n"; }
    };
}

#endif //VISUAL_SANDBOX_H
