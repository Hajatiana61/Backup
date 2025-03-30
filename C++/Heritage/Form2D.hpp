#ifndef _FORME_
#define _FORME_

using namespace std;

#include <iostream>
#include <string>

#define PI 3.14

class Form2D
{
    private:                // Attribut
        string c_name;
        string c_color;

    public:                 // Methode

        Form2D() = delete;
        /// Constructeur
        Form2D(string name, string color) noexcept;

        /// Mutateurs
        void setColor(std::string c_color);


        /// Accesseurs
        string getColor() const;
        string getName() const;



};


#endif
