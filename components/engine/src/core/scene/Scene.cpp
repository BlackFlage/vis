//
// Created by BlackFlage on 17.12.2021.
//

#include "Scene.h"

#include <ecs/components/BasicComponents.h>
#include "ecs/MainManager.h"
#include "resource_loaders/ResourcesManager.h"
#include "Types.h"

namespace vis
{
    Scene::Scene()
    {

    }

    Scene::Scene(const std::string &a_name)
    : Scene(a_name, {})
    {

    }

    Scene::Scene(const std::string& a_name, std::set<std::uint16_t> a_entities)
    {
        m_name = a_name;
        m_entities = std::move(a_entities);
        m_default_mesh_path = R"(..\engine_assets\meshes\)";
    }

    void Scene::on_load()
    {

    }

    void Scene::on_unload()
    {
        for(auto it = m_entities.begin(); it != m_entities.end(); it++)
        {
            MainManager::get_instance()->destroy_entity(*it);
        }
    }

    std::set<std::uint16_t>& Scene::get_entities()
    {
        return m_entities;
    }

    const std::string& Scene::get_name() const
    {
        return m_name;
    }

    void Scene::add_entity(std::uint16_t a_id)
    {
        m_entities.insert(a_id);
    }

    void Scene::remove_entity(std::uint16_t a_id)
    {
        m_entities.erase(a_id);
    }

    void Scene::add_entity(EntityType a_type)
    {
        std::uint16_t e = MainManager::get_instance()->create_entity();
        glm::vec3 scale(1.0f);

        if(a_type == EntityType::SPHERE)
        {
            scale = glm::vec3(0.3f);
        }

        MainManager::get_instance()->set_current_entity(e);
        m_entities.insert(e);

        MainManager::get_instance()->add_component(e, Transform{
                .m_position = glm::vec3(0.0f, 0.0f, 0.0f),
                .m_rotation = glm::vec3(0.0f),
                .m_scale = scale
        });

        if(a_type == EntityType::EMPTY)
        {
            return;
        }

        std::string suffix = get_suffix_from_type(a_type);
        MeshComponent mesh = { .m_id = ResourcesManager::get_instance()->load_mesh(m_default_mesh_path + suffix + ".obj")};

        MainManager::get_instance()->add_component(e, Color{
            .m_color = glm::vec3(0.7f)
        });

        MainManager::get_instance()->add_component(e, mesh);
    }

    std::string Scene::get_suffix_from_type(EntityType a_type)
    {
        switch(a_type)
        {
            case EntityType::CUBE:
                return "cube";
            case EntityType::SPHERE:
                return "sphere";
            default:
                return "cube";
        }
    }
}