#ifndef _CERCLE_
#define _CERCLE_

#include "Form2D.hpp"
#include <iostream>
#include <string>

using namespace std;

class Cercle : public Form2D
{
    using Form2D::Form2D;

    private:
        float c_Rayon;
        float c_surface;
        float c_circonf;

    public:
        Cercle() = delete;
        Cercle(string name, string color, float R) noexcept;

        /// Mutateurs;
        void setRayon(float rayon);
        /// Accesseurs

        float getRayon() const;
        float getSurface() const;
        float getCirconf() const;

};

#endif
