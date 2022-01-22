//
// Created by BlackFlage on 19.10.2021.
//

#ifndef MAIN_RENDERER_H
#define MAIN_RENDERER_H

#include "Shader.h"
#include "Camera.h"
#include "GL/glew.h"
#include "ecs/components/BasicComponents.h"
#include "Grid.h"
#include "Skybox.h"

namespace vis
{
    class Renderer
    {
    public:
        static void change_background_color(float r, float g, float b, float alpha);
        static void render(MeshRender& a_mesh);
        static void render_grid(const Grid& grid, Shader* shader);
        static void render_skybox(const Skybox* skybox, Shader* shader);

        static void begin();
        static void end();

        static void set_camera(Camera* m_camera);
        static void set_shader(Shader* shader);

        static void submit_data(const MeshRender& a_mesh);
    private:
        static void clean_buffers();
    private:
        static unsigned int vertex_array;
        static unsigned int vertex_buffer;
        static unsigned int index_buffer;
        static unsigned int vertex_buffer_end_ptr;
        static unsigned int index_buffer_end_ptr;
        static unsigned int indices_count;

        static Camera* m_camera;
        static Shader* m_shader;
    };
}

#endif //MAIN_RENDERER_H
