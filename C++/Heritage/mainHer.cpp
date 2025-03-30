#include <iostream>
#include <string>
#include "Form2D.hpp"


#include "Cercle.hpp"
#include "Scare.hpp"
#include "Rect.hpp"

using namespace std;

int main()
{
    Cercle C1{"cercle_1","rouge",9};
    Scare S1{"Carre_1","vert", 5};
    Rect R1{"Rectangle_1","bleu", 5, 11};

    cout<< " NOM: " << C1.getName() <<" COLOR: " << C1.getColor() << endl;
    cout<< " SURFACE: " << C1.getSurface() << " Perimètre: " << C1.getCirconf() << endl;

    return 0;
}
