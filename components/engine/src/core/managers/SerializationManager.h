//
// Created by BlackFlage on 16.02.2022.
//

#ifndef MAIN_SERIALIZATIONMANAGER_H
#define MAIN_SERIALIZATIONMANAGER_H

#include <unordered_map>

#include "Manager.h"
#include "../scene/Scene.h"
#include "ecs/components/BasicComponents.h"
#include "ecs/components/SceneCamera.h"

namespace vis
{
    class SerializationManager : public Manager
    {
    public:
        bool   start_up() override;
        bool   shut_down() override;
        static SerializationManager* get();

        bool   serialize_scene(Scene* scene, const std::string& path);
        Scene* deserialize_scene(const std::string& path);
    private:
        enum class ELEMENT_TYPE
        {
            SCENE,
            GAME_OBJECT,
            UNDEFINED
        };
    private:
        SerializationManager() = default;
        ~SerializationManager() override = default;

        void         serialize_entity_info(std::uint16_t number, std::uint16_t entity_id, std::ofstream& output);
        ELEMENT_TYPE deserialize_entity_info(std::string line);

        void serialize_transform_component(const Transform& transform, std::ofstream& output);
        void deserialize_transform_component();

        void serialize_color_component(const Color& color, std::ofstream& output);
        void deserialize_color_component();

        void serialize_mesh_component(const MeshComponent& mesh, std::ofstream& output);
        void deserialize_mesh_component();

        void serialize_scene_camera_component(SceneCamera& scene_camera, std::ofstream& output);
        void deserialize_scene_camera_component();

        void serialize_scene_data(Scene* scene, std::uint16_t number, std::ofstream& output);
        void deserialize_scene_data(Scene* scene, std::ifstream& input);
    private:
        std::unordered_map<ELEMENT_TYPE, std::uint16_t> m_element_to_id;
        static SerializationManager* m_instance;
        static float                 m_version;
        static std::string           m_component_prefix;
        static std::string           m_default_offset;
    };
}


#endif //MAIN_SERIALIZATIONMANAGER_H
