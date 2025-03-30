#ifndef _GAUSS_
#define _GAUSS_

double** Allocation2(double** board, double pd, double dd);
void SetDonne(double** board, double X1, double X2, double X3, double Y1, double Y2, double Y3, double Z1, double Z2, double Z3);
void SetQ(double* board, double Q1, double Q2, double Q3);
void Triangularisation(double** boadr,double* Quotien);
void Resolution(double** board ,double* Quotien, double* End);
void ShowAnswer(double* Answer);
#endif
