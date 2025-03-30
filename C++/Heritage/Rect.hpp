#ifndef _RECT_
#define _RECT_

#include "Form2D.hpp"
#include <iostream>
#include <string>


using namespace std;


class Rect : public Form2D
{
    using Form2D::Form2D;

    private:
        float c_long;
        float c_larg;
        float c_surface;
        float c_circonf;

    public:
        Rect() = delete;
        Rect(string name, string color, float Larg, float Long) noexcept;
        /// Mutateurs;

        void setLong(float LL);
        void setLarg(float ll);
        /// Accesseurs

        float getLong() const;
        float getLarg() const;
        float getSurface() const;
        float getCirconf() const;



};


#endif
