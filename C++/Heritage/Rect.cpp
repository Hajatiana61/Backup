#include <iostream>
#include <string>

#include "Rect.hpp"

using namespace std;

Rect::Rect(string name,string color, float Larg, float Long) noexcept : Form2D(name, color), c_larg(Larg), c_long(Long){}


float Rect::getLong() const
{
        return c_long;
}

float Rect::getLarg() const
{
        return c_larg;
}

float Rect::getSurface() const
{
    return c_larg*c_long;
}

float Rect::getCirconf() const
{
    return (c_larg+c_long)*2;
}
