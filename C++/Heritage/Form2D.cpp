#include <iostream>
#include <string>
#include "Form2D.hpp"

using namespace std;


Form2D::Form2D(string name ,string color) noexcept : c_name(name), c_color(color){}


string Form2D::getColor() const
{
    return c_color;
}


string Form2D::getName() const
{
    return c_name;
}

/*
void afficheSurface( float surface)
{
    cout<< " SURFACE: " << surface << endl;

}

void affichePerimetre(float perimetre)
{
    cout<< " PERIMETRE: " << perimetre << endl;

}
*/
