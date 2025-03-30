
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void gplot();
float find_Y(float X);
float Calc_D(float X);
void Descente_gradient(float X, float Y, float Alpha);
void optionChoose(float* X, float* Alpha);

int main()
{

    char* filename = "points.txt";
    float init_X = 0; float init_Y = 0;
    float Alpha = 0;

    optionChoose(&init_X, &Alpha);
    init_Y = find_Y(init_X);
/// Calcule moindre scare

    Descente_gradient(init_X, init_Y, Alpha);
// printf("value %f\n", init_Y);
    gplot();
/// show graphic
    optionChoose(&init_X, &Alpha);

    return 0;
}

void optionChoose(float* X, float* Alpha){

    int choice = 0;
    printf("\n\n -->> Valeur init_X: %f  Valeur Alpha: %f <<--\n", *X, *Alpha);
    printf("\n\n Afficher le graphique. (1)\n");
    printf(" Initiliser valeur X.   (2)\n");
    printf(" Definir l'Alpha.       (3)\n");
     printf(" Quitter.               (4)\n");
    printf("\n\n Enter votre choix : ");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf(" Affichage graphique. (1)\n");
            break;
        case 2:
            printf(" Entrer init_X : ");
            scanf("%f", X);
            optionChoose( X, Alpha);
            break;
        case 3:
            printf(" Entrer Alpha : ");
            scanf("%f", Alpha);
            optionChoose( X, Alpha);
            break;
        case 4:
            exit(0);
        default:
            optionChoose( X, Alpha);
    }

}
void Descente_gradient(float X, float Y, float Alpha)
{
    int boucle = 0;
    FILE* file = fopen("points2.txt","w");
    float X_tmp = 0.0, Y_tmp = 0.0;

    X_tmp = X - Alpha * Calc_D(X);Y_tmp = find_Y(X_tmp);
    fprintf(file,"%f, %f\n", X_tmp, Y_tmp);
    // X = X_tmp;

    while(fabsf(X - X_tmp) > 1e-7 && boucle < 10000)
    {
        X = X_tmp;
        X_tmp = X - Alpha * Calc_D(X);Y_tmp = find_Y(X_tmp);
        fprintf(file,"%f, %f\n", X_tmp, Y_tmp);
        boucle++;

    }
    fclose(file);

}

float Calc_D(float X)
{
    X = (( 2*X*cos(X) + (-sin(X)*X*X) - 1 ) ) / 10;
    return X;
}

float find_Y(float X)
{
    float Y_tmp = 0.0;

    Y_tmp = (X*X*cos(X)-X)/10;

    return Y_tmp;
}

void gplot()
{
    FILE* gp = popen("gnuplot -persist", "w");

    if(gp)
    {
/// parametrage de gnuplote
        // fprintf(gp , " set term wxt 800,500\n");
        fprintf(gp , " set title 'Test en C'\n");
        fprintf(gp , " set xlabel 'temps'\n");
        fprintf(gp , " set ylabel 'valeurs'\n");
        // fprintf(gp , " set datafile separator ','\n");
        // fprintf(gp , " set yzeroaxis\n");
        // fprintf(gp , " set xzeroaxis\n");
        fprintf(gp , " set yrange [%f:%f]\n", -5.0, 10.0);
        fprintf(gp , " set xrange [%f:%f]\n", -10.0, 10.0);


        fprintf(gp , " f(x) = (x*x*cos(x)-x)/10\n");
/// tracage de courbe avec gnuplote
        fprintf(gp , "plot 'points2.txt' using 1:2 with linespoints pt 7 ps 2, f(x) w l lc \"gray\" lw 3\n");
        fflush(gp);
        pclose(gp);

    }
}
