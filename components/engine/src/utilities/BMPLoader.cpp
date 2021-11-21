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
    unsigned char* BMPLoader::load_from_file(const std::string &a_file_path)
    {
        FILE* filePtr;
        BITMAPFILEHEADER bitmapFileHeader;
        BITMAPINFOHEADER bitmapInfoHeader;
        unsigned char* bitmapImage = nullptr;

        fopen_s(&filePtr, a_file_path.c_str(), "rb");

        if(!filePtr)
        {
            LOG_ERROR("Invalid file path: " + a_file_path);
            return nullptr;
        }

        fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
        fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

        if(bitmapFileHeader.bfType != (int)BMP_ID)
        {
            LOG_ERROR("Invalid file type! Expected BMP file.");
            return nullptr;
        }

        bitmapImage = new unsigned char[bitmapInfoHeader.biSizeImage];

        fseek(filePtr, (long)bitmapFileHeader.bfOffBits, SEEK_SET);
        fread(bitmapImage, bitmapInfoHeader.biSizeImage, 1, filePtr);

        if(bitmapImage == nullptr)
        {
            LOG_ERROR("Failed to read pixel data from file: " + a_file_path);
            fclose(filePtr);
            return nullptr;
        }

        fclose(filePtr);
        return bitmapImage;
    }
}
