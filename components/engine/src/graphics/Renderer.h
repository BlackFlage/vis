//
// Created by BlackFlage on 19.10.2021.
//

#ifndef MAIN_RENDERER_H
#define MAIN_RENDERER_H

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

namespace vis
{
    class Renderer
    {
    public:
        static void change_background_color(float r, float g, float b, float alpha);
        static void render(float r, float g, float b, float size, Shader* a_shader);
        static void render(Model* a_model, Camera* a_camera, Shader* a_shader);
    };
}

#endif //MAIN_RENDERER_H
