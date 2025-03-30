#include <stdio.h>
#include <math.h>
double Puissance_rec(double Nombre, int up);

int main()
{
    double FI = 0, Answer=1;
    int Puissance = 49;
    FI = ((sqrt(5)-1)/2);            /// Valeur à Calculer
    //FI = 3;
    /// Par iteration
    for (int p=0; p < Puissance; p++)
        Answer = FI * Answer;

    printf("Answer = %f\n", Answer);
    // Par recurrance
/*
    Answer = Puissance_rec(FI, Puissance);
    printf("Answer = %f\n", Answer);

*/
    return 0;
}

double Puissance_rec(double Nombre, int up)
{

    if(up == 0)
        return 0;
    if(up == 1)
        return Nombre;
    else
        return Nombre * Puissance_rec(Nombre, up-1);

}
