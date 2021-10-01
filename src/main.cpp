#include <iostream>
#include "Window.h"

int main()
{
    vis::Window* window = vis::Window::create_window(320, 480, "Chuj");
    window->show_window();

    while(true)
    {
        window->pull_events();
    }

    return 0;
}
