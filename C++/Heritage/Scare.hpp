#ifndef _SCARE_
#define _SCARE_

#include "Form2D.hpp"
#include <iostream>
#include <string>


using namespace std;


class Scare:public Form2D
{
    using Form2D::Form2D;

    private:
        float c_side;
        float c_surface;
        float c_circonf;

    public:

        Scare() = delete;
         /// Constructeur
        Scare(string name, string color, float side) noexcept;

        /// Mutateurs;
        void setSide(float cote);

        /// Accesseurs
        float getSide() const;
        float getSurface() const;
        float getCirconf() const;

};


#endif
