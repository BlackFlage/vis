//
// Created by BlackFlage on 13.02.2022.
//

#ifndef MAIN_GLOBALREGISTER_H
#define MAIN_GLOBALREGISTER_H

#include <list>

#include "Manager.h"

namespace vis
{
    class GlobalRegister
    {
    public:
        void register_manager(Manager* manager)
        {
            m_managers.push_back(manager);
        }

        void unregister_manager(Manager* manager)
        {
            m_managers.remove(manager);
        }

        void start_up_managers()
        {
            for(auto& manager : m_managers)
            {
                manager->start_up();
            }
        }

        void shut_down_managers()
        {
            for(auto& manager : m_managers)
            {
                manager->shut_down();
            }
        }
    private:
        std::list<Manager*> m_managers;
    };
}

#endif //MAIN_GLOBALREGISTER_H
