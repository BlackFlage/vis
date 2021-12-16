//
// Created by BlackFlage on 13.11.2021.
//

#ifndef MAIN_OBJLOADER_H
#define MAIN_OBJLOADER_H

#include <string>
#include "ecs/components/BasicComponents.h"
#include <glm/glm.hpp>

#define MODELS_PATH "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\models\\"

namespace vis
{
    class OBJLoader
    {
    public:
        static Mesh load_from_file(const std::string& a_file_path, const std::string& a_name);
        static Mesh load_from_models(const std::string& a_path_from_models_dir, const std::string& a_name);
    };
}


#endif //MAIN_OBJLOADER_H
