
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void gplot(float* X, float* Y, int dim);
void getData(char* file, float** X, float** Y, int dim);
float* newVect(int dim);
void lagrange(FILE* gp, float* X, float* Y, int dim, float* minY, float* maxY);
void lineaire(FILE* gp, float* X, float* Y, int dim);
void tridiag(float *a, float *b, float *c,float *r, float *u, int n);
void problem(char* message);
void Cspline(FILE* gp, float* X, float* Y, int dim);
void solveS2(float* lambda, float* rho, float *Y, float *s2, int dim);
float findFx(float x, float* Xd, float* Yd,int  dim, int j);
float findPx(float x, float* Xd, float* Yd,int  dim);
float findSx(float x,float Dx, float* s2, float a, float b, float* xd, int dim, int j);

int main()
{

    char* filename = "Interpolant.txt";
    int dim = 7;
    float* X = NULL; float* Y = NULL;


/// Getdata
    getData(filename, &X, &Y,dim);

/// Traitement

    gplot(X, Y, dim);
/// show graph

    return 0;
}
void getData(char* file, float** X, float** Y, int dim){
    FILE* fic = NULL;
    float xt = 0, yt = 0, *xdt = NULL, *ydt = NULL;


    fic = fopen(file, "r");

    if(fic != NULL){
// Allocation et lecture des donnees

        xdt = newVect(dim); ydt = newVect(dim);

        for(int i = 0; i < dim; i++)
        {
            fscanf(fic,"%f %f", &xt, &yt);xdt[i] = xt; ydt[i] = yt;
        }
        fclose(fic);

        *X = xdt; *Y = ydt;
    }
    else
            printf("Impossible d'ouvrir le fichier\n");


}

float* newVect(int dim)
{
    float* vect = NULL;
    vect = malloc(dim*sizeof(float*));
    return vect;
}

void gplot(float* X, float* Y, int dim)
{
    FILE* gp = popen("gnuplot -persist", "w");
    char *chaine; char* all;

    float ymax = 0., ymin = 0., xmax = X[dim-1] + 1, xmin = X[0] - 1;

    if(gp)
    {
/// parametrage de gnuplote

        // fprintf(gp , " set term wxt 900,500\n");
        fprintf(gp , " set title 'Test en C'\n");
        fprintf(gp , " set xlabel 'temps'\n");
        fprintf(gp , " set ylabel 'valeurs'\n");


// insert into $DATA
        fprintf(gp, " $data1 << EOF\n");
        for(int tmp = 0; tmp < dim; tmp++)
        {
            fprintf(gp, "%f %f\n", X[tmp], Y[tmp]);
        }
        fprintf(gp, "EOF\n");

//  Methodes
        lineaire(gp , X, Y, dim);

        lagrange(gp, X, Y, dim, &ymin, &ymax);

        Cspline(gp, X, Y, dim);

        fprintf(gp , " set yrange [%f:%f]\n", ymin, ymax);
        fprintf(gp , " set xrange [%f:%f]\n", xmin, xmax);
/// tracage de courbe avec gnuplote

        fprintf(gp, "plot $data1 using 1:2 with points pt 7 ps 2, ");
        fprintf(gp, "$data2 using 1:2 with lines lc \"gray\" lw 3, " );
        fprintf(gp, "$data3 using 1:2 with lines lc \"green\" lw 3, " );
        fprintf(gp, "$data4 using 1:2 with lines lc \"red\" lw 3\n " );

        fflush(gp);
        pclose(gp);

     }
}
void Cspline(FILE* gp, float* X, float* Y, int dim)
{
    float* lambda = NULL; float* rho = NULL; float* Dx = NULL;

    lambda = newVect(dim); rho = newVect(dim); Dx = newVect(dim);


    for(int i = 0; i < dim-1; i++)  Dx[i] = X[i+1] - X[i];
    for(int i = 1; i < dim; i++)  lambda[i] = Dx[i] / (Dx[i-1] + Dx[i]);
    for(int i = 0; i < dim-1; i++)  rho[i] = 1 - lambda[i+1];
// Les coefficient à calculer
    float* s2 = NULL;
    float* Yt = NULL;
    float* a = NULL; float* b = NULL;
    a = newVect(dim-1); b = newVect(dim-1); s2 = newVect(dim); s2[0] = 0; s2[dim-1] = 0;

// second membre du system tridiag. sym. pour le calcul de *s2
    Yt = newVect(dim-1);
    for(int j = 1; j < dim-1; j++ )
    {
        Yt[j-1] = 6./(Dx[j-1]+Dx[j])*((Y[j+1]-Y[j])/Dx[j] - (Y[j]-Y[j+1])/Dx[j-1]);
    }

// Calcul de S2

    s2++;           // Les tableaux commencent à 1
    solveS2(lambda, rho, Yt, s2, dim-2);
    s2--;

// Calcule de a et b
    for(int j = 0; j < dim-1; j++)
    {
        a[j] = Y[j]/Dx[j] - s2[j]*Dx[j]/6;
        b[j] = Y[j+1]/Dx[j] - s2[j+1]*Dx[j]/6;

    }

// gnuplot


    float Alpha = 0.005;                                 /// Interpolation spacing
    float ytmp = 0.0;

    fprintf(gp, " $data4 << EOF\n");
     for(int j = 0; j < dim-1; j++)
    {
        float xtmp = X[j];float xmax = X[j+1];
        while( xtmp <=  xmax)
        {

            ytmp = findSx(xtmp, Dx[j], s2, a[j], b[j],  X, dim, j);

            fprintf(gp, "%f %f\n", xtmp, ytmp);
            xtmp += Alpha;
        }
    }
    fprintf(gp, "EOF\n");


}

float findSx(float x,float Dx, float* s2, float a, float b, float* xd, int dim, int j)
{
    float yt = 0.;

    yt = (1/(6.*Dx)) * ((s2[j]*(xd[j+1]-x)*(xd[j+1]-x)*(xd[j+1]-x))+s2[j+1]*(x-xd[j])*(x-xd[j])) + a*(xd[j+1]-x) + b*(x-xd[j]);

    return yt;
}

void lineaire(FILE* gp, float* X, float* Y, int dim)
{
    float Alpha = 0.05;

    float ytmp = 0.0; float Yj = 0.0;
/*
    for(int tmp = 0; tmp < dim-1; tmp++)
    {
        fprintf(gp , " A%d(x) = %f + (x - %f)*((%f - %f)/(%f-%f))\n", tmp+1, Y[tmp], X[tmp], Y[tmp+1], Y[tmp], X[tmp+1], X[tmp]);
    }
*/

    fprintf(gp, " $data2 << EOF\n");
    for(int j = 0; j < dim-1; j++)
    {
        float xtmp = X[j];float xmax = X[j+1];
        while( xtmp <=  xmax)
        {

            ytmp = findFx(xtmp, X, Y, dim, j);

            // printf(" %f %f\n", xtmp, ytmp);
            fprintf(gp, "%f %f\n", xtmp, ytmp);
            xtmp += Alpha;
        }
    }
    fprintf(gp, "EOF\n");
}

float findFx(float x, float* Xd, float* Yd,int  dim, int j)
{
    float yt = 0.;

    yt = Yd[j] + (x - Xd[j])*((Yd[j+1] - Yd[j])/(Xd[j+1] - Xd[j]));

    return yt;
}

void lagrange(FILE* gp, float* X, float* Y, int dim, float* minY, float* maxY)
{
    float Alpha = 0.005;

    float xtmp = X[0];float xmax = X[6];
    float ytmp = 0.0; float Yj = 0.0;

    fprintf(gp, " $data3 << EOF\n");
        while( xtmp <=  xmax)
        {

            ytmp = findPx(xtmp, X, Y, dim);

            if(ytmp < *minY) *minY = ytmp - 2;
            if(ytmp > *maxY) *maxY = ytmp + 2;

            fprintf(gp, "%f %f\n", xtmp, ytmp);
            xtmp += Alpha;
        }
    fprintf(gp, "EOF\n");

}

float findPx(float x, float* Xd, float* Yd,int  dim)
{
    float yt = 0., Pj = 1.;
    for(int j = 0;j < dim;j++){
        Pj = 1.;
        for(int k = 0;k < dim;k++){
            if(k == j)
                continue;
            else
                Pj =  Pj * (x - Xd[k])/(Xd[j] - Xd[k]);
        }
        yt += Yd[j] * Pj;
    }
    return yt;
}

void solveS2(float* lambda, float* rho, float *Y, float *s2, int dim){
    float *B=NULL, *C=NULL, *D=NULL;
    int j=0;

    B = newVect(dim);			// diagonale principale
    C = newVect(dim);			// première surdiagonale
    D = newVect(dim);			// première sous-diagonale
    for(j=0; j<dim; j++){
        B[j] = 2;
        C[j] = lambda[j];		// on ne suppose pas que les points sont équidistants
        D[j] = rho[j];
    }
    tridiag(D,B,C,Y,s2,dim);
 }

/* Tridiagonal matrix solver.  Nonzero diagonals of the matrix are
   represented by arrays a, b, and c (see Numerical Recipes).
   All arrays start at 0
 [b_0 c_0                  ] [ u_0 ]   [ r_0 ]
 [a_1 b_1 c_1              ] [ u_1 ]   [ r_1 ]
 [          ...            ] [ ... ] = [ ... ]
 [        a_n-2 b_n-2 c_n-2] [u_n_2]   [r_n-2]
 [              a_n-1 b_n-1] [u_n-1]   [r_n-1]
 */
void tridiag(float *a, float *b, float *c,float *r, float *u, int n){
    int j;
    float bet, gam[n];

    if (b[0] == 0.0) problem("Division par 0");
    u[0] = r[0] / (bet=b[0]);
    for (j = 1; j < n; j++) {
        gam[j] = c[j-1]/bet;
        bet = b[j] - a[j]*gam[j];
        if (bet == 0.0) problem("Division par 0");
        u[j] = (r[j]-a[j]*u[j-1]) / bet;
    }
    for (j = n-2; j >= 0; j--)
        u[j] -= gam[j+1]*u[j+1];
}

void problem(char* message)
{
    printf("\n error: %s\n\n", message);
}
