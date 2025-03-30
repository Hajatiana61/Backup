#include <iostream>
#include <string>
#include "fonct.hpp"
#include <vector>
#include <cmath>
#include <time.h>
#include <unistd.h>

using namespace std;

circle::circle(string nom, string color, int X, int Y, int rayon)
{
    c_name = nom;
    c_color = color;
    c_X = X; c_Y = Y;
    c_rayon = rayon;


}


void circle::setName(std::string nom)
{
    c_name = nom;
}
void circle::setColor(std::string color)
{
    c_color = color;
}
void circle::setAbsisse(int X)
{
    c_X = X;
}
void circle::setOrdonne(int Y)
{
    c_Y = Y;
}
void circle::setRayon(int rayon)
{
    c_rayon = rayon;
}


string circle::getName()
{
    return c_name;
}
string circle::getColor()
{
    return c_color;
}
int circle::getAbsisse()
{
    return c_X;
}
int circle::getOrdonne()
{
    return c_Y;
}
int circle::getRayon()
{
    return c_rayon;
}



string random_color(int color)
{
    std::string tmp1{};
    if (color == 0)tmp1 = "rouge";
    if (color == 1)tmp1 = "vert";
    if (color == 2)tmp1 = "bleu";
    if (color == 3)tmp1 = "marron";
    if (color == 4)tmp1 = "noir";
    if (color == 5)tmp1 = "gris";
    if (color == 6)tmp1 = "jaune";

    return tmp1;

}

int random_Axe()
{
    //sleep(1);
    //srand(3900*time(NULL));
    int axe = rand() % (10 + 11) - 10;
    return axe;
}

int random_R()
{
   // sleep(1);
    //srand(6500*time(NULL));
    int rayon = rand() % (5-1+1) + 1;
    return rayon;
}

void Distance_Center(vector<circle> disque,int nb, vector<int> coord_x, vector<int> coord_y, vector<int> rayon)
{
    int x1, x2, y1, y2;double Distance = 0;
    //cout << "nb: "<< coord_x[0] << endl;

    for(auto tmp3{0}; tmp3 < nb; tmp3++)
    {
        for(auto var{tmp3+1}; var < nb ; var++)
        {
            x1 = coord_x[tmp3];
            y1 = coord_y[tmp3];
            x2 = coord_x[var];
            y2 = coord_y[var];

            Distance = Calcule_Distance(x1, x2, y1, y2);
            //cout << "x1: "<< x2 << endl;
            //cout << "Dist: "<< Distance << endl;

            Check_Case(disque, Distance, rayon, tmp3, var, x1, x2, y1, y2);

        }

    }

}

double Calcule_Distance(int x1, int x2, int y1, int y2)
{
    double X1 = x1, X2 = x2, Y1 = y1, Y2 = y2;
    double D = 0;
    D =sqrt(P((X2 - X1), 2) + P((Y2 - Y1), 2));

    return D;
}

double P(double down,int up)
{
		double answer=1;

		if(up==0)return 1;

		else{
			while(up!=0){
					answer=answer*down;
					up=up-1;
			}

			return answer;
		}
}

void Check_Case(vector<circle> disque, double D, vector<int> R, int num1, int num2, int x1, int x2, int y1, int y2)
{
    double R1 = R[num1]; double R2 = R[num2];
    double inter_x1, inter_x2, inter_y1, inter_y2;


    if ( D > R1+R2 )
    {
        Rapport_False(disque, num1, num2, "Les cercles sont très éloignés", "Sans interaction", D, x1, x2, y1, y2 );
    }

    else if ( D < fabs(R1 - R2))
    {

        Rapport_False(disque, num1, num2, "Un cercle est à l'interieur de l'autre", " Sans interaction", D, x1, x2, y1, y2);
    }

    else if ((D = 0 )&& (R1 = R2))
    {
        Rapport_False(disque,num1, num2, "Les cercle sont confondus", " Infinité d'interactions", D, x1, x2, y1, y2);

    }
    else if (D = R1 + R2)
    {
        double a , b, h;
        double Mx, My;
        a = Calcul_A(D, R1, R2);
        b = Calcul_B(D , R1, R2);
        h = Calcul_H(R1, a);
        coord_Midle(D, a, &Mx, &My, x1, x2, y1, y2);

        inter_x1 = Mx - (h*(y2 - y1)/D);
        inter_y1 = My + (h*(x2 - x1)/D);
        inter_x2 = Mx + (h*(y2 - y1)/D);
        inter_y2 = My - (h*(x2 - x1)/D);

        Rapport_True(disque,num1, num2, "Il n'y a qu'un seul point d'interaction", inter_x1, inter_x2, inter_y1, inter_y2, D, x1, x2, y1, y2);

    }
    else if ((D = R1 - R2) || (D = R2 - R1))
    {
        double a , b, h;
        double Mx, My;
        a = Calcul_A(D, R1, R2);
        b = Calcul_B(D , R1, R2);
        h = Calcul_H(R1, a);
        coord_Midle(D, a, &Mx, &My, x1, x2, y1, y2);

        inter_x1 = Mx - (h*(y2 - y1)/D);
        inter_y1 = My + (h*(x2 - x1)/D);
        inter_x2 = Mx + (h*(y2 - y1)/D);
        inter_y2 = My - (h*(x2 - x1)/D);

        Rapport_True(disque, num1, num2, "Il n'y a qu'un seul point d'interaction", inter_x1, inter_x2, inter_y1, inter_y2, D, x1, x2, y1, y2);

    }
    else if (D < R1 + R2)
    {
       double a , b, h;
       double Mx, My;
        a = Calcul_A(D, R1, R2);
        b = Calcul_B(D , R1, R2);
        h = Calcul_H(R1, a);
        coord_Midle(D, a, &Mx, &My, x1, x2, y1, y2);

        inter_x1 = Mx - (h*(y2 - y1)/D);
        inter_y1 = My + (h*(x2 - x1)/D);
        inter_x2 = Mx + (h*(y2 - y1)/D);
        inter_y2 = My - (h*(x2 - x1)/D);

        Rapport_True(disque, num1, num2, "Il y a deux points d'interaction", inter_x1, inter_x2, inter_y1, inter_y2, D, x1, x2, y1, y2);
    }


}

double Calcul_A(double D, double R1, double R2)
{
    double tmp = (P(R1, 2) - P(R2, 2) + P(D, 2))/(2*D);
    return tmp;
}

double Calcul_B(double D, double R1, double R2)
{
    double tmp = (P(R2, 2) - P(R1, 2) + P(D, 2))/(2*D);
    return tmp;
}

double Calcul_H(double R1, double a)
{
    double hauteur = sqrt(P(R1, 2) - P(a, 2));
    return hauteur;
}

void coord_Midle(double D, double a,double *Mx, double *My, int x1, int x2, int y1, int y2)
{
    *Mx = x1 + ((a/D) * (x2 - x1));
    *My = y1 + ((a/D) * (y2 - y1));

}

void Rapport_False(vector<circle> disque, int c1, int c2, string texte1, string texte2, double D, int x1, int x2, int y1, int y2)
{
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;
    cout << "Rapport \"Cercle "<< c1+1 <<" et Cercle "<< c2+1 << "\""<< endl<< endl;
    cout << "Coordonnées : ("<< x1 <<" ; "<< y1 <<" )"<<" et "<<"( "<< x2 <<" ; "<< y2 <<" )" << endl;
    cout << "Couleurs : "<< disque[c1].getColor() <<" et "<< disque[c2].getColor() << endl << endl;

    cout << "Distance : "<< D << endl;
    cout << "Situation :"<< texte1 <<"\ninteraction :"<< texte2 << endl;
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;

    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;

}

void Rapport_True(vector<circle> disque, int c1, int c2, string texte,double c1_x, double c2_x, double c1_y, double c2_y, double D, int x1, int x2, int y1, int y2)
{
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;
    cout << "Rapport \"Cercle "<< c1+1 <<" et Cercle "<< c2+1 << "\""<< endl << endl;
    cout << "Coordonnées : ("<< x1 <<" ; "<< y1 <<" )"<<" et "<<"( "<< x2 <<" ; "<< y2 <<" )" << endl;
    cout << "Couleurs : "<< disque[c1].getColor() <<" et "<< disque[c2].getColor() << endl << endl;
    cout << "Distance : "<< D << endl;
    cout << "Situation : \""<< texte << "\""<< endl;
    cout << "Interaction : A( "<< c1_x <<" ; "<< c1_y << " )" <<"         B( "<< c2_x << " ; " << c2_y << " )"<< endl;
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;

    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;
    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl;


}
