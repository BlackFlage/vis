//
// Created by BlackFlage on 20.11.2021.
//

#include "BMPLoader.h"
#include <fstream>
#include "Logger.h"
#include <Wingdi.h>

#define BMP_ID 0x4D42

namespace vis
{
    uint8_t* BMPLoader::load_from_file(const std::string &a_file_path, int* a_width, int* a_height, bool a_flip_vertically)
    {
        uint8_t* dataBuffer[2] = {nullptr, nullptr};
        uint8_t* bitmapImage = nullptr;
        BITMAPFILEHEADER* bitmapFileHeader;
        BITMAPINFOHEADER* bitmapInfoHeader;

        std::ifstream file(a_file_path, std::ios::binary);
        if(!file)
        {
            LOG_ERROR("Invalid file path: " + a_file_path);
            return nullptr;
        }

        dataBuffer[0] = new uint8_t[sizeof(BITMAPINFOHEADER)];
        dataBuffer[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

        file.read((char*)dataBuffer[0], sizeof(BITMAPFILEHEADER));
        file.read((char*)dataBuffer[1], sizeof(BITMAPINFOHEADER));
        bitmapFileHeader = (BITMAPFILEHEADER*)dataBuffer[0];
        bitmapInfoHeader = (BITMAPINFOHEADER*)dataBuffer[1];

        if(bitmapFileHeader->bfType != (int)BMP_ID)
        {
            LOG_ERROR("Invalid file type! Expected BMP file.");
            return nullptr;
        }

        bitmapImage = new uint8_t[bitmapInfoHeader->biSizeImage];

        file.seekg(bitmapFileHeader->bfOffBits, std::ifstream::beg);

        *a_width = bitmapInfoHeader->biWidth;
        *a_height = std::abs(bitmapInfoHeader->biHeight);

        if(!bitmapInfoHeader->biSizeImage)
        {
            bitmapInfoHeader->biSizeImage = (*a_width) * (*a_height) * 3;
        }

        const int padding = (4 - (*a_width * 3) % 4) % 4;

        if(a_flip_vertically)
        {
            for(int i = (*a_height - 1) * 3; i >= 0; i -= 3)
            {
                int index = i * (*a_width);
                for(int j = 0; j < *a_width * 3; j += 3)
                {
                    bitmapImage[index + j + 2] = (uint8_t)file.get();
                    bitmapImage[index + j + 1] = (uint8_t)file.get();
                    bitmapImage[index + j] = (uint8_t)file.get();

                    file.seekg(padding, std::ios::cur);
                }
            }
        }
        else
        {
            file.read(reinterpret_cast<char*>(bitmapImage), bitmapInfoHeader->biSizeImage);

            uint8_t tempPixel;
            for(int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3)
            {
                tempPixel = bitmapImage[i];
                bitmapImage[i] = bitmapImage[i + 2];
                bitmapImage[i + 2] = tempPixel;
            }
        }

        file.close();
        delete[] dataBuffer[0];
        delete[] dataBuffer[1];

        return bitmapImage;
    }
}
