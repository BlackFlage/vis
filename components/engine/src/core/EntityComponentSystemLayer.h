//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_ENTITYCOMPONENTSYSTEMLAYER_H
#define MAIN_ENTITYCOMPONENTSYSTEMLAYER_H

#include <memory>

#include "Layer.h"
#include "ecs/EntityManager.h"
#include "ecs/ComponentManager.h"
#include "ecs/SystemManager.h"

namespace vis
{
    class EntityComponentSystemLayer : public Layer
    {
    public:
        ~EntityComponentSystemLayer() override = default;

        void on_attach() override;
        void on_detach() override;

        void on_event(Event& a_event) override;
        void on_update(float a_delta_time) override;
        void on_render() override;
    private:
        std::unique_ptr<EntityManager> m_entity_manager;
        std::unique_ptr<ComponentManager> m_component_manager;
        std::unique_ptr<SystemManager> m_system_manager;
    };
}

#endif //MAIN_ENTITYCOMPONENTSYSTEMLAYER_H
