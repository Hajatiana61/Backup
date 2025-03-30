#include <iostream>
#include <string>

#include "Cercle.hpp"

#define PI 3.14

using namespace std;

Cercle::Cercle(string name,string color, float R) noexcept : Form2D(name, color), c_Rayon(R){}

float Cercle::getRayon() const
{
    return c_Rayon;
}

float Cercle::getSurface() const
{
    return c_Rayon*c_Rayon*PI;
}

float Cercle::getCirconf() const
{
    return 2*c_Rayon*PI;
}
