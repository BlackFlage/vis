//
// Created by BlackFlage on 20.11.2021.
//

#ifndef MAIN_BMPLOADER_H
#define MAIN_BMPLOADER_H

#include <string>

#define TEXTURES_PATH "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\"

namespace vis
{
    class BMPLoader
    {
    public:
        static uint8_t* load_from_file(const std::string& a_file_path, int* a_width, int* a_height, bool a_flip_vertically);
    };
}


#endif //MAIN_BMPLOADER_H
