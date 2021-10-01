//
// Created by BlackFlage on 01.10.2021.
//

#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "Window.h"

namespace vis
{
    class Application
    {
    public:
        Application();
        ~Application();

        void run();
        void initialize();
    private:
        Window* window;
    };
}


#endif //VISUAL_APPLICATION_H
