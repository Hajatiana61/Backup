
#include "stdio.h"

void gplot(float ymin, float ymax);

int main()
{
    float ymin = -2, ymax = 10; //, xmin = -8, xmax = 10;

    gplot(ymin, ymax);

    return 0;
}

void gplot(float ymin, float ymax)
{
    FILE* gp = popen("gnuplot -persist", "w");

    if(gp)
    {
/// parametrage de gnuplote
        // fprintf(gp , " set term wxt 800,500\n");
        fprintf(gp , " set title 'Test en C'\n");
        fprintf(gp , " set xlabel 'temps'\n");
        fprintf(gp , " set ylabel 'valeurs'\n");
        fprintf(gp , " set yzeroaxis\n");
        fprintf(gp , " set xzeroaxis\n");
        // fprintf(gp , " set yrange [%f:%f]\n", ymin, ymax);
        // fprintf(gp , " set xrange [%f:%f]\n", xmin, xmax);
/// tracage de courbe avec gnuplote
        // fprintf(gp , "plot sin(x), cos(x)\n");
        fprintf(gp , "plot 'points.txt' with linespoints pt 7 ps 2,sin(x) w l lc \"gray\" lw 3, cos(x) w l lc \"blue\" lw 3\n");

        fflush(gp);
        pclose(gp);

    }


}
