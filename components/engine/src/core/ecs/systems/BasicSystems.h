//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_BASICSYSTEMS_H
#define MAIN_BASICSYSTEMS_H

#include <vector>

#include "ecs/System.h"
#include "ecs/MainManager.h"
#include "ecs/components/BasicComponents.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

namespace vis
{
    class PhysicsSystem : public System
    {
    public:
        void on_update(float a_dt)
        {
            for(const std::uint16_t& id : m_entities)
            {
                auto& rigid_body = main_manager->get_component<RigidBody>(id);
                auto& transf = main_manager->get_component<Transform>(id);

                transf.m_position.x += rigid_body.vel_x * a_dt;
                transf.m_position.y += rigid_body.vel_y * a_dt;
                transf.m_position.z += rigid_body.vel_z * a_dt;
            }
        }
    };

    class RendererSystem : public System
    {
    public:
        void on_render()
        {
            Renderer::begin();

            auto it = m_entities.begin();
            while(it != m_entities.end())
            {
                auto& transform = main_manager->get_component<Transform>(*it);
                auto& color = main_manager->get_component<Color>(*it);
                auto& mesh = main_manager->get_component<Mesh>(*it);

                glm::mat4 transform_mat = glm::mat4(1.0f);
                transform_mat = glm::translate(transform_mat, transform.m_position);

                transform_mat = glm::rotate(transform_mat, glm::radians(transform.m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
                transform_mat = glm::rotate(transform_mat, glm::radians(transform.m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
                transform_mat = glm::rotate(transform_mat, glm::radians(transform.m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

                transform_mat = glm::scale(transform_mat, transform.m_scale);

                MeshRender mesh_render = MeshRender{.m_vertices = mesh.m_vertices,
                        .m_indices = mesh.m_indices,
                        .m_model = transform_mat,
                        .m_color = color.m_color,
                        .m_geometry_type = mesh.m_geometry_type};
                Renderer::render(mesh_render);

                it++;
            }

            Renderer::end();
        }

    private:
        static std::vector<VertexRender> compose_vertexes(const Mesh& a_mesh, const glm::mat4& a_transform, const Color& a_color)
        {
            std::vector<VertexRender> vrs;

            for(const auto& v : a_mesh.m_vertices)
            {
                vrs.push_back(VertexRender{
                        .m_position = v.m_position,
                        .m_normals = v.m_normals,
                        .m_textureCoords = v.m_textureCoords,
                        .m_color = a_color.m_color,
                        .m_transform = a_transform
                });
            }

            return vrs;
        }
    };

    class EntityTrackSystem : public System
    {
    public:
        void on_update(float a_dt)
        {
            for(auto& entity : m_entities)
            {
                auto& transform = main_manager->get_component<Transform>(entity);

                if(transform.m_position.y > 30.0f)
                {
                    transform.m_position.y = -25.0f;
                }
            }
        }
    };
}

#endif //MAIN_BASICSYSTEMS_H
