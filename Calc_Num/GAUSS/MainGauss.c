#include <stdio.h>
#include <stdlib.h>
#include "Gauss.h"

int main()
{
/// Data Setting

    double** tab = NULL;                            // Adress du matrice problem
    double* Answer = malloc(sizeof(double)*3);      // Adress de veteur Solution
    double* tab4 = malloc(sizeof(double)*3);        // Adress du second membre

    tab = Allocation2(tab,3,3);                      // Allocation du matrice du problem
    SetDonne(tab, 4, 3, 2, 8, 8, 9, 12, 13, 18);    // Entrer des donnees matrice problem
    SetQ(tab4, 4 , 5, 11);

/// Calcul de Gauss

    Triangularisation(tab, tab4);
    Resolution(tab, tab4, Answer);

/// Affichage des resultats
    ShowAnswer(Answer);

    return 0;
}


