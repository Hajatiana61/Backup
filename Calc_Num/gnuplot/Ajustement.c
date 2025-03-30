
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void find_fonction(int N, float* a, float* b, float* X, float* Y);
void find_barre(int N, float* xb, float* yb, float* X, float* Y);
void find_variance(int N,float xb, float yb, float* cov, float* var, float* X, float* Y);
void getData(char* filename, float* xmin, float* xmax, float* ymin, float* ymax, int *dim, float **xd, float **yd);
void gplot(float xmin, float xmax, float ymin, float ymax, float a, float b);
void ShowData(int dim, float value_1 , float* value_2, char* smg);
float* newVect(int dim);

int main()
{
    // float ymin = -2, ymax = 10; //, xmin = -8, xmax = 10;

    char* filename = "points.txt";
    int dim = 0;
    float xmax = 0, xmin = 0, ymin = 0, ymax = 0;
    float* xd = NULL; float* yd = NULL;
    float a = 0, b = 0;

/// recuperer les donnees

    getData(filename, &xmin, &xmax, &ymin, &ymax, &dim, &xd, &yd);
/// Calcule moindre scare

    find_fonction(dim, &a, &b, xd, yd);

/// show graphic
    gplot(xmin, xmax, ymin, ymax, a, b);

    ShowData(dim, ymax, xd, "max Y");

    return 0;
}

void find_fonction(int N, float* a, float* b, float* X, float* Y)
{
    float x_barre = 0, y_barre = 0;
    float cov = 0, var = 0;

    find_barre(N, &x_barre, &y_barre, X, Y);
    find_variance(N, x_barre, y_barre, &cov, &var, X, Y);

    *a = cov/var;
    *b = y_barre - (*a*x_barre);

}

void find_variance(int N,float xb, float yb, float* cov, float* var, float* X, float* Y)
{
    for(int i = 0; i < N; i++)*var = *var + ((X[i] - xb)*(X[i] - xb)); *var = *var/N;

    for(int i = 0; i < N; i++)*cov = *cov + ((X[i] - xb)*(Y[i] - yb)); *cov = *cov/N;

}
void find_barre(int N, float* xb, float* yb, float* X, float* Y)
{
    *xb = 0;*yb = 0;
    for(int i = 0; i < N; i++)*xb += X[i];*xb = *xb/N;

    for(int i = 0; i < N; i++)*yb += Y[i];*yb = *yb/N;
}

void getData(char* filename, float* xmin, float* xmax, float* ymin, float* ymax, int *dim, float **xd, float **yd)
{
    FILE *pf = NULL;
    float xt = 0, yt = 0, *xdt = NULL, *ydt = NULL;

    pf=fopen(filename,"r");

        if(pf != NULL){
            fscanf(pf, "%d", dim);
// Allocation et lecture des donnees

            xdt = newVect(*dim); ydt = newVect(*dim);
            // *ymin = -1e8; *ymax = 1e8;
            *ymin = 0; *ymax = 0;

            for(int i = 0; i < *dim; i++)
            {
                fscanf(pf,"%f, %f", &xt, &yt);xdt[i] = xt; ydt[i] = yt;
                if(ydt[i] < *ymin) *ymin = ydt[i];
                if(ydt[i] > *ymax) *ymax = ydt[i];
                if(xdt[i] < *xmin) *xmin = xdt[i];
                if(xdt[i] > *xmax) *xmax = xdt[i];

            }
            fclose(pf);

            *xd = xdt; *yd = ydt;
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

void ShowData(int dim, float value_1 , float* value_2, char* smg)
{
    printf(" dimension : %d\n", dim);
    printf("%s : \n %f  \n", smg, value_1 );

    for(int i = 0; i < dim; i++)
        printf(" point[%d] = %f\n", i, value_2[i]);

}
void gplot(float xmin, float xmax, float ymin, float ymax, float a, float b)
{
    FILE* gp = popen("gnuplot -persist", "w");

    if(gp)
    {
/// parametrage de gnuplote
        // fprintf(gp , " set term wxt 800,500\n");
        fprintf(gp , " set title 'Test en C'\n");
        fprintf(gp , " set xlabel 'temps'\n");
        fprintf(gp , " set ylabel 'valeurs'\n");
        fprintf(gp , " set datafile separator ','\n");
        // fprintf(gp , " set yzeroaxis\n");
        // fprintf(gp , " set xzeroaxis\n");
        fprintf(gp , " set yrange [%f:%f]\n", ymin, ymax);
        fprintf(gp , " set xrange [%f:%f]\n", xmin, xmax);


        printf("\ntest : %f\n", xmax);
        fprintf(gp , " f(x) = %f*x+%f\n", a, b);
/// tracage de courbe avec gnuplote
        fprintf(gp , "plot 'points.txt' using 1:2 with linespoints pt 7 ps 2,sin(x) w l lc \"gray\" lw 3, cos(x) w l lc \"blue\" lw 3, f(x)\n");
        fflush(gp);
        pclose(gp);

    }
}
