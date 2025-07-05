#ifndef bmp
#define bmp

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

void writeBMP(std::string filename, uint32_t width, uint32_t height, uint8_t* pixelData);

#endif