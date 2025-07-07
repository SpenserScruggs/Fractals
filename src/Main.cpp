#include <iostream>
#include <fstream>
#include <cstdint>
#include <thread>
#include <future>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "bmp.h"
#include "Cmath.h"

uint16_t iter = 50;
uint32_t width = 900;
uint32_t height = 900;
float scale = 2.0f;
int strength = 1000;
int range = 1000;

//Seahorse Valley	-0.745428, 0.113009i
//Elephant Valley	-1.25, 0.0i
//Triple Spiral	-0.088 + 0.654i
//Mini Mandelbrot	-0.1015 + 0.633i
//Mandelbrot Antenna	-0.156 + 1.03225i

float R_center = -0.128f;
float Im_center = 0.654f;

const uint32_t max_threads = std::thread::hardware_concurrency();
const uint32_t threads = std::min(width * height, max_threads > 0 ? max_threads : 8);

float R_it = 1.0f;
float Im_it = 1.0f;

std::array<float, 2> func(std::array<float, 2>& a, int depth, float R_it, float Im_it, std::array<float, 2> original) {  
    std::array<float, 2> comp_iter = {R_it, Im_it};

    if (depth == iter){
        original = a;
        //Cadd(original, comp_iter);
    }

    if (depth > 0) {
        //Csin(comp_iter);
        //Cmulti(a, comp_iter);
        Cmulti(a, a);
        Cadd(a, original);

        return func(a, depth - 1, R_it, Im_it, original);
    }
    else {
        return a;
    }
}

void generate(uint8_t* image, int start, int end){
    for (int i = start; i < end; i++) {
        float x = i%width*2.0f*scale/width - 1.0f*scale - R_center;
        float y = (1.0f*scale - ((int)i/width)*2.0f*scale/height)/(width/height) - Im_center;

        std::array<float, 2> pos = { x, y };
        func(pos, iter, R_it, Im_it, {0.0f, 0.0f});

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
    uint8_t* pixelData = new uint8_t[width * height *3];
    
    // for(int i = 0; i < 2; i++){
    //     std::string filename = "../Outputs/output" + formatToThreeDigits(i) + ".bmp";
    //     generate(pixelData, 0, width*height);
    //     writeBMP(filename, width, height, pixelData);
    // }
 
    for(int i = 0; i < 50; i++){
        std::string filename = "../Outputs/mandelbrot/output" + formatToThreeDigits(i) + ".bmp";
        multi_threading(pixelData);
        writeBMP(filename, width, height, pixelData);
        
        //Im_it += 0.5f;
        //R_it += 0.05f;
        scale = 2.0f * std::pow(0.90, i+2);

    }

    delete[] pixelData;
    return 0;
}