#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include "bmp.h"

#pragma pack(push, 1)
struct BMPFileHeader {
    char signature[2] = {'B', 'M'};   // 2 bytes
    uint32_t fileSize;                // 4 bytes
    uint16_t reserved1 = 0;           // 2 bytes
    uint16_t reserved2 = 0;           // 2 bytes
    uint32_t dataOffset;             // 4 bytes
};
#pragma pack(pop)
#pragma pack(push, 1)
struct DIBHeader {
    uint32_t headerSize = 40;
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bitsPerPixel = 24;
    uint32_t compression = 0;
    uint32_t dataSize;
    int32_t horizontalResolution = 2835;
    int32_t verticalResolution = 2835;
    uint32_t numColors = 0;
    uint32_t importantColors = 0;
};
#pragma pack(pop)

void writeBMP(std::string filename, uint32_t width, uint32_t height, uint8_t* pixelData) {
    BMPFileHeader fileHeader;
    DIBHeader dibHeader;

    dibHeader.width = width;
    dibHeader.height = height;
    dibHeader.dataSize = width * height * 3;

    fileHeader.dataOffset = sizeof(BMPFileHeader) + sizeof(DIBHeader);
    fileHeader.fileSize = fileHeader.dataOffset + dibHeader.dataSize;

    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error creating BMP file: " << filename << std::endl;
        return;
    }

    outputFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outputFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));
    outputFile.write(reinterpret_cast<char*>(pixelData), dibHeader.dataSize);

    outputFile.close();
    std::cout << "BMP file created: " << filename << std::endl;
}