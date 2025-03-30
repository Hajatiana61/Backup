#include <iostream>
#include <string>

#include "Scare.hpp"

using namespace std;


Scare::Scare(string name,string color, float side) noexcept : Form2D(name, color), c_side(side){}

float Scare::getSide() const
{
    return c_side;
}

float Scare::getSurface() const
{
    return c_side*c_side;
}

float Scare::getCirconf() const
{
    return c_side*4;
}
