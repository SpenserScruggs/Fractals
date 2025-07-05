#include <iostream>
#include <fstream>
#include <cstdint>
#include <thread>
#include <future>
#include <string>
#include <sstream>
#include <iomanip>
#include "bmp.h"
#include "Cmath.h"

uint16_t iter = 10;
uint32_t width = 5000;
uint32_t height = 2500;
uint32_t scale = 5;
int strength = 1000;
int range = 1000;

const uint32_t threads = width / height * 100;

float R_it = 0.0f;
float Im_it = 0.0f;

std::array<float, 2> func(std::array<float, 2>& a, int depth, float R_it, float Im_it) {    
    std::array<float, 2> b = a;
    std::array<float, 2> c = {R_it, Im_it};
    if (depth > 0) {
        Cmulti(b, c);
        Cadd(a, b);
        Csin(a);
        return func(a, depth - 1, R_it, Im_it);
    }
    else {
        return a;
    }
}

void generate(uint8_t* image, int start, int end){
    for (int i = start; i < end; i++) {
        std::array<float, 2> pos = { (i%width*2.0f*scale/width - 1.0f*scale), (1.0f*scale - ((int)i/width)*2.0f*scale/height)/2 };
        func(pos, iter, R_it, Im_it);
        std::array<unsigned char, 3> rgb = Crgb(pos, strength, range);
        image[i*3] = rgb[0];
        image[i*3+1] = rgb[1];
        image[i*3+2] = rgb[2];
        if(start == 0 && i%width == 0){
            std::cout << i*100.0f/end << "%\n";
        }
    }
}

void multi_threading(uint8_t* image){
    std::vector<std::thread> myThread;
    
    for(int i = 0; i < threads; i++){
        //i*width*height/threads, (i+1)*width*height/threads
        myThread.emplace_back(generate, image, i*width*height/threads, (i+1)*width*height/threads);
    }
    for (std::thread& t : myThread) {
        t.join();
    }
}

std::string formatToThreeDigits(int num) {
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << num;
    return ss.str();
}

int main() {
    std::string filename = "../Outputs/output.bmp";
    uint8_t* pixelData = new uint8_t[width * height * 3];
    // writeBMP(filename, width, height, pixelData);
    // for(int i = 0; i < 1; i++){
    //     generate(pixelData, 0, width*height);
    //     writeBMP(filename, width, height, pixelData);
    // }
    for(int i = 0; i < 10; i++){
        std::string filename = "../Outputs/output" + formatToThreeDigits(i) + ".bmp";
        multi_threading(pixelData);
        writeBMP(filename, width, height, pixelData);
        Im_it += 0.05f;
    }

    delete[] pixelData;
    return 0;
}