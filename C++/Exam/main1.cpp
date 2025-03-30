#include <iostream>
#include <string>
#include "fonct.hpp"
#include <vector>
#include <time.h>
#include <unistd.h>

using namespace std;

int main()
{
    ///
    Start:
    ///
    srand(time(NULL));
    int circle_Nomber = rand() % (7-2+1) + 2;
    vector<circle> tab_cercle;
    vector<int> var_x;
    vector<int> var_y;
    vector<int> rayon;
    sleep(1);

    cout << "/---------------------------------------------------------------------------------------------------------------/" << endl << endl;

    cout << "\t\t\t NOMBRE DU CERCLE \" "<< circle_Nomber << "\""<< endl;
    string color{};

    for(auto tmp{0}; tmp < circle_Nomber; tmp++)
    {
         color = random_color(tmp);
         var_x.push_back(random_Axe());
         var_y.push_back(random_Axe());
         rayon.push_back(random_R());

        tab_cercle.push_back(circle("circle", color, var_x[tmp], var_y[tmp], rayon[tmp]));

    }
    Distance_Center(tab_cercle, circle_Nomber, var_x, var_y, rayon);
  //  cout << "testeX: "<< var_x[2] << endl;
  //  cout << "testeX1: "<< var_x[3] << endl;

    char c;
    cout << "\n\nACTUALISER ?(y/n)";
    cin >> c;
    if ((c == 'y') ||(c == 'Y') || (c == 'o') || (c == 'O') )
        goto Start;
    else
        exit;


    return 0;
}
