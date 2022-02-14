//
// Created by BlackFlage on 13.02.2022.
//

#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H

#include <list>
#include "Logger.h"

namespace vis
{
    class Manager
    {
    public:
        Manager()
        {
            m_initialized = false;
        }

        virtual ~Manager() = default;

        virtual bool start_up()
        {
            LOG_INFO("Starting up: {0}", typeid(*this).name());

            for(auto& manager : m_dependencies)
            {
                if(!manager->start_up())
                {
                    LOG_ERROR("Failed to start up: {0}", typeid(*this).name());
                    return false;
                }
            }

            LOG_INFO("Successfully started up: {0}", typeid(*this).name() );
            return true;
        }

        virtual bool shut_down()
        {
            LOG_INFO("Shutting down: {0}", typeid(*this).name());

            for(auto& manager : m_dependencies)
            {
                if(!manager->shut_down())
                {
                    return false;
                }
            }

            LOG_INFO("Successfully shut down: {0}", typeid(*this).name() );
            return true;
        }
    protected:
        std::list<Manager*> m_dependencies;
        bool m_initialized;
    };
}

#endif //MAIN_MANAGER_H
