//
// Created by BlackFlage on 16.02.2022.
//

#include <fstream>

#include "SerializationManager.h"
#include "ecs/MainManager.h"

namespace vis
{
    SerializationManager* SerializationManager::m_instance;
    float                 SerializationManager::m_version;
    std::string           SerializationManager::m_component_prefix;
    std::string           SerializationManager::m_default_offset;

    SerializationManager *SerializationManager::get()
    {
        if(!m_instance)
        {
            LOG_INFO("Creating SerializationManager");
            m_instance = new SerializationManager();
        }

        return m_instance;
    }

    bool SerializationManager::start_up()
    {
        if(!Manager::start_up())
        {
            LOG_ERROR("Failed to start up dependencies of SerializationManager");
        }

        m_version = 0.1f;
        m_element_to_id.insert({ELEMENT_TYPE::UNDEFINED, 0});
        m_element_to_id.insert({ELEMENT_TYPE::SCENE, 1});
        m_element_to_id.insert({ELEMENT_TYPE::GAME_OBJECT, 2});
        m_component_prefix = "      ";
        m_default_offset   = "   ";

        return true;
    }

    bool SerializationManager::shut_down()
    {
        if(!Manager::shut_down())
        {
            LOG_ERROR("Failed to shut down dependencies of SerializationManager");
        }

        delete m_instance;
        m_instance = nullptr;

        return true;
    }

    bool SerializationManager::serialize_scene(Scene *scene, const std::string &path)
    {
        std::ofstream file(path);
        std::uint16_t current_element_number = 0;

        if(!file.is_open())
        {
            LOG_ERROR("Failed to open file for serialization: {0}", path.c_str());
            return false;
        }

        file << "%version " << m_version << '\n';

        serialize_scene_data(scene, current_element_number,file);
        current_element_number++;

        for(const auto& entity : scene->get_entities())
        {
            serialize_entity_info(current_element_number, entity, file);
            current_element_number++;
        }

        file.close();

        LOG_INFO("Successfully saved file: {0}", path.c_str());

        return false;
    }

    Scene *SerializationManager::deserialize_scene(const std::string &path)
    {
        return nullptr;
    }

    void SerializationManager::serialize_entity_info(std::uint16_t number, std::uint16_t entity_id, std::ofstream& output)
    {
        auto main_manager = MainManager::get_instance();

        output << "--- !u!" << m_element_to_id.at(ELEMENT_TYPE::GAME_OBJECT) << " ";
        output << "&" << number << '\n';
        output << "GameObject:\n";
        output << m_default_offset << "m_Name: " << main_manager->get_entity(entity_id).get_name() << '\n';

        Signature sig = main_manager->get_entity_signature(entity_id);

        if(sig[main_manager->get_component_type<Transform>()])
        {
            const auto& transform = main_manager->get_component<Transform>(entity_id);
            serialize_transform_component(transform, output);
        }
        if(sig[main_manager->get_component_type<Color>()])
        {
            const auto& color = main_manager->get_component<Color>(entity_id);
            serialize_color_component(color, output);
        }
        if(sig[main_manager->get_component_type<MeshComponent>()])
        {
            const auto& mesh = main_manager->get_component<MeshComponent>(entity_id);
            serialize_mesh_component(mesh, output);
        }
        if(sig[main_manager->get_component_type<SceneCamera>()])
        {
            auto& scene_camera = main_manager->get_component<SceneCamera>(entity_id);
            serialize_scene_camera_component(scene_camera, output);
        }
    }

    SerializationManager::ELEMENT_TYPE SerializationManager::deserialize_entity_info(std::string line)
    {
        return SerializationManager::ELEMENT_TYPE::GAME_OBJECT;
    }

    void SerializationManager::serialize_scene_data(Scene *scene, std::uint16_t number, std::ofstream &output)
    {
        output << "--- !u!" << m_element_to_id.at(ELEMENT_TYPE::SCENE) << " ";
        output << "&" << number << '\n';
        output << "Scene:\n";
        output << m_default_offset << "m_Name: " << scene->get_name() << '\n';
    }

    void SerializationManager::deserialize_scene_data(Scene* scene, std::ifstream& input)
    {

    }

    void SerializationManager::serialize_transform_component(const Transform &transform, std::ofstream &output)
    {
        output << m_default_offset << "Transform:\n";
        output << m_component_prefix << "m_Position: { " << transform.m_position.x << " , " << transform.m_position.y << " , " << transform.m_position.z << " }\n";
        output << m_component_prefix << "m_Rotation: { " << transform.m_rotation.x << " , " << transform.m_rotation.y << " , " << transform.m_rotation.z << " }\n";
        output << m_component_prefix << "m_Scale: { " << transform.m_scale.x << " , " << transform.m_scale.y << " , " << transform.m_scale.z << " }\n";
    }

    void SerializationManager::deserialize_transform_component()
    {

    }

    void SerializationManager::serialize_color_component(const Color &color, std::ofstream &output)
    {
        output << m_default_offset << "Color:\n";
        output << m_component_prefix << "m_Color: { " << color.m_color.x << " , " << color.m_color.y << " , " << color.m_color.z << " }\n";
    }

    void SerializationManager::deserialize_color_component()
    {

    }

    void SerializationManager::serialize_mesh_component(const MeshComponent &mesh, std::ofstream &output)
    {
        output << m_default_offset << "Mesh:\n";
        output << m_component_prefix << "m_ID: " << mesh.m_id << '\n';
    }

    void SerializationManager::deserialize_mesh_component()
    {

    }

    void SerializationManager::serialize_scene_camera_component(SceneCamera &scene_camera, std::ofstream &output)
    {
        output << m_default_offset << "SceneCamera:\n";
        output << m_component_prefix << "m_UseSkybox: " << scene_camera.get_use_skybox() << '\n';
        output << m_component_prefix << "m_PerspectiveView: " << scene_camera.get_use_perspective_view() << '\n';
        output << m_component_prefix << "m_FOV: " << scene_camera.get_fov() << '\n';
        output << m_component_prefix << "m_zNear: " << scene_camera.get_z_near() << '\n';
        output << m_component_prefix << "m_zFar: " << scene_camera.get_z_far() << '\n';

        auto& clear_color = scene_camera.get_clear_color();
        output << m_component_prefix << "m_ClearColor: { " << clear_color[0] << " , " << clear_color[1] << " , " << clear_color[2] << " }\n";
    }

    void SerializationManager::deserialize_scene_camera_component()
    {

    }
}