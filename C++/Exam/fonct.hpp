#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class circle
{
    private:                // Attribut
        string c_name;
        string c_color;
        int c_X;
        int c_Y;
        int c_rayon;

    public:                 // Methode

        /// Constructeur
        circle(string nom, string color, int X, int Y, int rayon);

        /// Mutateurs
        void setName(std::string nom);
        void setColor(std::string color);
        void setAbsisse(int X);
        void setOrdonne(int Y);
        void setRayon(int rayon);

        /// Accesseurs
        string getName();
        string getColor();
        int getAbsisse();
        int getOrdonne();
        int getRayon();

};


string random_color(int color);
int random_Axe();
int random_R();
void Distance_Center(vector<circle> disque, int nb, vector<int> coord_x, vector<int> coord_y, vector<int> rayon);
double Calcule_Distance(int x1, int x2, int y1, int y2);
double P(double down,int up);
void Check_Case(vector<circle> disque, double D, vector<int> R, int num1, int num2, int x1, int x2, int y1, int y2);
double Calcul_A(double D, double R1, double R2);
double Calcul_B(double D, double R1, double R2);
double Calcul_H(double R1, double a);
void coord_Midle(double D, double a,double *Mx, double *My, int x1, int x2, int y1, int y2);
void Rapport_False(vector<circle> disque, int c1, int c2, string texte1, string texte2, double D, int x1, int x2, int y1, int y2);
void Rapport_True(vector<circle> disque, int c1, int c2, string texte,double c1_x, double c2_x, double c1_y, double c2_y, double D, int x1, int x2, int y1, int y2);

#endif
