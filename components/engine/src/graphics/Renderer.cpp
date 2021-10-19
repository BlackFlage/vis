//
// Created by BlackFlage on 19.10.2021.
//

#include "Renderer.h"
#include "GL/glew.h"

namespace vis
{
    void Renderer::change_background_color(float r, float g, float b, float alpha)
    {
        glClearColor(r, g, b, alpha);
    }
}

