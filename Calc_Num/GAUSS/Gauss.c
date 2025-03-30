#include "Gauss.h"
#include <stdlib.h>
#include <stdio.h>

double** Allocation2(double** board, double pd, double dd)
{
    board = malloc(sizeof(double) * pd);

    for(int tmp = 0; tmp < dd; tmp ++)
        *(board+tmp) = malloc(sizeof(double*)*dd);

    return board;
}

void SetDonne(double** board, double X1, double X2, double X3,double Y1, double Y2, double Y3, double Z1, double Z2, double Z3)
{
    board[0][0] = X1;board[0][1] = Y1;board[0][2] = Z1;
    board[1][0] = X2;board[1][1] = Y2;board[1][2] = Z2;
    board[2][0] = X3;board[2][1] = Y3;board[2][2] = Z3;


}

void SetQ(double* board, double Q1, double Q2, double Q3)
{
    board[0] = Q1;
    board[1] = Q2;
    board[2] = Q3;
}

void Triangularisation(double** board, double* Quotien)
{
    int k = 0;
    for(int i = 1; i < 3; i++)
    {

        for(int j = 1; j < 3; j++)
        {
            board[i][j] = board[i][j] - ((board[i][k]/board[k][k]) * board[k][j]);
        }

        Quotien[i] =  Quotien[i] - ((board[i][k]/board[k][k]) * Quotien[k]);
        board[i][k] = 0;

    }k++;



    board[2][2] = board[2][2] - ((board[2][k]/board[k][k]) * board[k][2]);


    Quotien[2] =  Quotien[2] - ((board[2][k]/board[k][k]) * Quotien[k]);
    board[2][k] = 0;

    //Quotien[2] = 15;
    //printf("Les valeurs: %f\n", board[1][2]);
}

void Resolution(double** board,double* Quotien, double* unkown)
{
    /// Calcule de Z
    unkown[2]=Quotien[2]/board[2][2];
    /// Calcule de Y
    unkown[1]=(Quotien[1]-board[1][2]*unkown[2]) / board[1][1];
    /// Calcule de X
    unkown[0]=(Quotien[0]-(board[0][2]*unkown[2])-(board[0][1]*unkown[1])) / board[0][0];

}

void ShowAnswer(double* Answer)
{
    printf("Les solutions sont :\nX = %f\nY = %f\nZ = %f\n", Answer[0], Answer[1], Answer[2]);

}
