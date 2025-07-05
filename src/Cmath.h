#ifndef Cmath
#define Cmath

#include <iostream>
#include <array>
#include <vector>

void Cadd(std::array<float, 2>&, std::array<float, 2>);

void Cmulti(std::array<float, 2>&, std::array<float, 2>);

void Cdiv(std::array<float, 2>&, std::array<float, 2>);

void Csub(std::array<float, 2>&, std::array<float, 2>);

void Csin(std::array<float, 2>&);

void Ccos(std::array<float, 2>&);

void Ctan(std::array<float, 2>&);

void Cr_th(std::array<float, 2>&);

int clamp(int x, int min, int max);

std::array<unsigned char, 3> Crgb(std::array<float, 2>& a, float strength, float range);


#endif