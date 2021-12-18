//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_SYSTEMMANAGER_H
#define MAIN_SYSTEMMANAGER_H

#include <unordered_map>
#include <memory>

#include "Types.h"
#include "System.h"
#include "Logger.h"
#include "Entity.h"

namespace vis
{
    class SystemManager
    {
    public:
        void init()
        {
            m_systems = std::unordered_map<const char*, std::shared_ptr<System>>();
            m_signatures = std::unordered_map<const char*, Signature>();
        }

        template<typename T>
        std::shared_ptr<T> register_system()
        {
            const char* system_name = typeid(T).name();

            if(m_systems.find(system_name) != m_systems.end())
            {
                LOG_WARNING("Trying to register system: {0} more than once!", system_name);
                return nullptr;
            }

            auto system = std::make_shared<T>();
            m_systems.insert({system_name, system});

            return system;
        }

        template<typename T>
        void set_signature(const Signature& a_signature)
        {
            const char* system_name = typeid(T).name();

            if(m_systems.find(system_name) == m_systems.end())
            {
                LOG_WARNING("Trying to set system signature before registering system: {0}", system_name);
                return;
            }

            m_signatures.insert({system_name, a_signature});
        }

        void on_entity_destroyed(std::uint16_t a_id)
        {
            for(auto& system_pair : m_systems)
            {
                auto& system = system_pair.second;
                system->m_entities.erase(a_id);
            }
        }

        void on_entity_signature_changed(std::uint16_t a_id, const Signature& a_signature)
        {
            for(auto& system_pair : m_systems)
            {
                const auto& name = system_pair.first;
                auto& system = system_pair.second;
                const auto& sys_signature = m_signatures[name];

                if((a_signature & sys_signature) == sys_signature)
                {
                    system->m_entities.insert(a_id);
                }
                else
                {
                    system->m_entities.erase(a_id);
                }
            }
        }
    private:
        std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
        std::unordered_map<const char*, Signature> m_signatures;
    };
}

#endif //MAIN_SYSTEMMANAGER_H
