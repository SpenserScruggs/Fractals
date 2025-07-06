#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include "bmp.h"

#pragma pack(push, 1)
struct BMPHeader {
    // BMP file header
    char signature[2] = {'B', 'M'};
    uint32_t fileSize;
    uint32_t reserved = 0;
    uint32_t dataOffset;
    uint32_t headerSize = 40; // size of the BMP header (40 bytes for BMP v3)
    uint32_t width;
    uint32_t height;
    uint16_t planes = 1;
    uint16_t bitsPerPixel = 24; // 24 bits per pixel (RGB)
    uint32_t compression = 0; // no compression
    uint32_t dataSize; // size of the pixel data
    uint32_t horizontalResolution = 2835; // 72 dpi
    uint32_t verticalResolution = 2835; // 72 dpi
    uint32_t numColors = 0; // number of colors in the palette (0 means default 2^n)
    uint32_t importantColors = 0; // 0 means all colors are important
};
#pragma pack(pop)

void writeBMP(std::string filename, uint32_t width, uint32_t height, uint8_t* pixelData) {
    BMPHeader header;
    header.width = width;
    header.height = height;
    header.dataSize = width * height * 3; // 3 bytes per pixel (RGB)

    if (!pixelData) {
    std::cerr << "Invalid pixel data pointer.\n";
    return;
    }

    std::ofstream outputFile(filename, std::ios::binary);

    if (!outputFile) {
        std::cerr << "Error creating BMP file: " << filename << std::endl;
        return;
    }

    outputFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outputFile.write(reinterpret_cast<char*>(pixelData), header.dataSize);

    outputFile.close();

    std::cout << "BMP file created: " << filename << std::endl;
}