#include <iostream>
#include "Window.h"
#include "Application.h"

int main()
{
    auto app = new vis::Application();

    app->initialize();
    app->run();

    delete app;

    return 0;
}
