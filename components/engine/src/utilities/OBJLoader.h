//
// Created by BlackFlage on 13.11.2021.
//

#ifndef MAIN_OBJLOADER_H
#define MAIN_OBJLOADER_H

#include <string>
#include "Mesh.h"
#include <glm/glm.hpp>

namespace vis
{
    class OBJLoader
    {
    public:
        static Mesh* load_from_file(const std::string& a_file_path);
    private:
    };
}


#endif //MAIN_OBJLOADER_H
