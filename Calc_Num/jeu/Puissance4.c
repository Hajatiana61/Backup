#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void showTables(int pd, int dd, char*** fl);
void Alloc(int pd, int dd, char**** champ);
void GameStart(int pd, int dd, int P, char*** field);
void showP4(int pd, int dd, char*** fl);
void addJeton(int pd, int dd, char*** field, int* JCP, int JP, char* jeton);
void initColPos(int dd, int** col);
bool verifyP4(int pd, int dd, char*** field, int* JCP, int JP);
bool horizontale(int pd, int dd, char*** field, int* JCP, int JP);
bool verticale(int pd, int dd, char*** field, int* JCP, int JP);
bool oblique1(int pd, int dd, char*** field, int* JCP, int JP);
bool oblique2(int pd, int dd, char*** field, int* JCP, int JP);


int main(){

/// all Data
    int pd = 6,                     // line number
    dd = 7,                         // Collum number
    player = 1;                     // Player clu
    char*** field;                  // Gameboard

    Alloc(pd, dd, &field);

/// Traitement
    GameStart(pd, dd, player, field);

/// result

    //showP4(pd, dd, field);
    return 0;
}


void GameStart(int pd, int dd, int P,  char*** field)
{
    int JP = 0;                             // Jeton Position
    int* JCP = NULL;                        // Jeton Collum Position
    initColPos(dd, &JCP);

    while(1){

        showTables(pd, dd, field);
        if(P == 1){

            while(1){
                printf("\n\033[1;33m Player 1: \033[0m");
                scanf("%d", &JP);

                if(JP > 0 && JP < 8)break;
            }

            addJeton(pd, dd, field, JCP, JP,"O");

            if(verifyP4(pd, dd, field, JCP, JP)){
                printf("\n Victory >>\033[1;32m Player 1 \033[0m<<\n\n");
                break;
            }
            else
                P = 2;
        }

        else if(P == 2){

           while(1){
                printf("\n\033[1;33m Player 2: \033[0m");
                scanf("%d", &JP);

                if(JP > 0 && JP < 8)break;
            }

            addJeton(pd, dd, field, JCP, JP,"X");

            if(verifyP4(pd, dd, field, JCP, JP)){
                printf("\n Victory >>\033[1;32m Player 2 \033[0m<<\n\n");
                break;
            }
            else
                P = 1;
        }


         system("clear");
    }

}

bool horizontale(int pd, int dd, char*** field, int* JCP, int JP)
{
    // There is 4 possiblities
    int line = JCP[JP] - 1;
    int col = JP-1;
    char* pointX = NULL;
    int cp1 = 0, cp2 = 0, cp3 = 0;
    int cmax = dd, cmin = 0;
    char tmp[200];
    int color = 31;

    pointX = field[line][col];

    // X O O O
    cp1 = col + 1; cp2 = col + 2; cp3 = col + 3;
    if((cp1 < cmax) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[line][cp1]) && (pointX == field[line][cp2]) && (pointX == field[line][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[line][cp1] =  tmp;
            field[line][cp2] =  tmp;
            field[line][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O X O O
    cp1 = col - 1; cp2 = col + 1; cp3 = col + 2;
    if((cp1 >= cmin) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[line][cp1]) && (pointX == field[line][cp2]) && (pointX == field[line][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[line][cp1] =  tmp;
            field[line][cp2] =  tmp;
            field[line][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }


    // O O X O
    cp1 = col - 2; cp2 = col - 1; cp3 = col + 1;
    if((cp1 >= cmin) && (cp2 >= cmin) && (cp3 < cmax)){
        if((pointX == field[line][cp1]) && (pointX == field[line][cp2]) && (pointX == field[line][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[line][cp1] =  tmp;
            field[line][cp2] =  tmp;
            field[line][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O O O X
    cp1 = col - 3; cp2 = col - 2; cp3 = col - 1;
    if((cp1 >= cmin) && (cp2 >= cmin) && (cp3 >= cmin)){
        if((pointX == field[line][cp1]) && (pointX == field[line][cp2]) && (pointX == field[line][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[line][cp1] =  tmp;
            field[line][cp2] =  tmp;
            field[line][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }


    return false;
}

bool verticale(int pd, int dd, char*** field, int* JCP, int JP)
{
    // There is 4 possiblities
    int line = JCP[JP] - 1;
    int col = JP-1;
    char* pointX = NULL;
    int lp1 = 0, lp2 = 0, lp3 = 0;
    int lmax = pd, lmin = 0;
    char tmp[200];
    int color = 31;

    pointX = field[line][col];

    // O
    // O
    // O
    // X
    lp1 = line + 1; lp2 = line + 2; lp3 = line + 3;
    if((lp1 < lmax) && (lp2 < lmax) && (lp3 < lmax)){
        if((pointX == field[lp1][col]) && (pointX == field[lp2][col]) && (pointX == field[lp3][col])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][col] =  tmp;
            field[lp2][col] =  tmp;
            field[lp3][col] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O
    // O
    // X
    // O
    lp1 = line - 1; lp2 = line + 1; lp3 = line + 2;
    if((lp1 >= lmin) && (lp2 < lmax) && (lp3 < lmax)){
        if((pointX == field[lp1][col]) && (pointX == field[lp2][col]) && (pointX == field[lp3][col])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][col] =  tmp;
            field[lp2][col] =  tmp;
            field[lp3][col] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O
    // O
    // X
    // O
    lp1 = line - 2; lp2 = line - 1; lp3 = line + 1;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 < lmax)){
        if((pointX == field[lp1][col]) && (pointX == field[lp2][col]) && (pointX == field[lp3][col])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][col] =  tmp;
            field[lp2][col] =  tmp;
            field[lp3][col] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // X
    // O
    // O
    // O
    lp1 = line - 3; lp2 = line - 2; lp3 = line - 1;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 >= lmin)){
        if((pointX == field[lp1][col]) && (pointX == field[lp2][col]) && (pointX == field[lp3][col])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][col] =  tmp;
            field[lp2][col] =  tmp;
            field[lp3][col] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    return false;
}

bool oblique1(int pd, int dd, char*** field, int* JCP, int JP)
{

   // There is 4 possiblities
    int line = JCP[JP] - 1;
    int col = JP-1;
    char* pointX = NULL;
    int lp1 = 0, lp2 = 0, lp3 = 0;
    int cp1 = 0, cp2 = 0, cp3 = 0;
    int lmax = pd, lmin = 0;
    int cmax = dd, cmin = 0;
    char tmp[200];
    int color = 31;


    pointX = field[line][col];

    //       O
    //     O
    //   O
    // X
    lp1 = line + 1; lp2 = line + 2; lp3 = line + 3;
    cp1 = col + 1; cp2 = col + 2; cp3 = col + 3;
    if((lp1 < lmax) && (lp2 < lmax) && (lp3 < lmax) && (cp1 < cmax) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    //       O
    //     O
    //   X
    // O
    lp1 = line - 1; lp2 = line + 1; lp3 = line + 2;
    cp1 = col - 1; cp2 = col + 1; cp3 = col + 2;
    if((lp1 >= lmin) && (lp2 < lmax) && (lp3 < lmax) && (cp1 >= cmin) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    //       O
    //     X
    //   O
    // O
    lp1 = line - 2; lp2 = line - 1; lp3 = line + 1;
    cp1 = col - 2; cp2 = col - 1; cp3 = col + 1;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 < lmax) && (cp1 >= cmin) && (cp2 >= cmin) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    //       X
    //     O
    //   O
    // O
    lp1 = line - 3; lp2 = line - 2; lp3 = line - 1;
    cp1 = col - 3; cp2 = col - 2; cp3 = col - 1;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 >= lmin) && (cp1 >= cmin) && (cp2 >= cmin) && (cp3 >= cmin)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    return false;
}

bool oblique2(int pd, int dd, char*** field, int* JCP, int JP)
{

    // There is 4 possiblities
    int line = JCP[JP] - 1;
    int col = JP-1;
    char* pointX = NULL;
    int lp1 = 0, lp2 = 0, lp3 = 0;
    int cp1 = 0, cp2 = 0, cp3 = 0;
    int lmax = pd, lmin = 0;
    int cmax = dd, cmin = 0;
    char tmp[200];
    int color = 31;


    pointX = field[line][col];

    // O
    //   O
    //     O
    //       X
    lp1 = line + 3; lp2 = line + 2; lp3 = line + 1;
    cp1 = col - 3; cp2 = col - 2; cp3 = col - 1;
    if((lp1 < lmax) && (lp2 < lmax) && (lp3 < lmax) && (cp1 < cmax) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O
    //   O
    //     X
    //       O
    lp1 = line + 2; lp2 = line + 1; lp3 = line - 1;
    cp1 = col - 2; cp2 = col - 1; cp3 = col + 1;
    if((lp1 >= lmin) && (lp2 < lmax) && (lp3 < lmax) && (cp1 >= cmin) && (cp2 < cmax) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // O
    //   X
    //     O
    //       O
    lp1 = line + 1; lp2 = line - 1; lp3 = line - 2;
    cp1 = col  - 1; cp2 = col + 1; cp3 = col + 2;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 < lmax) && (cp1 >= cmin) && (cp2 >= cmin) && (cp3 < cmax)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    // X
    //   O
    //     O
    //       O
    lp1 = line - 1; lp2 = line - 2; lp3 = line - 3;
    cp1 = col + 1; cp2 = col + 2; cp3 = col + 3;
    if((lp1 >= lmin) && (lp2 >= lmin) && (lp3 >= lmin) && (cp1 >= cmin) && (cp2 >= cmin) && (cp3 >= cmin)){
        if((pointX == field[lp1][cp1]) && (pointX == field[lp2][cp2]) && (pointX == field[lp3][cp3])){

            sprintf(tmp, "\033[1;%dm%s\033[0m", color, pointX);
            field[line][col] =  tmp;
            field[lp1][cp1] =  tmp;
            field[lp2][cp2] =  tmp;
            field[lp3][cp3] =  tmp;

            showP4(pd, dd, field);
            return true;
        }
    }

    return false;
}

bool verifyP4(int pd, int dd, char*** field, int* JCP, int JP)
{
    // Horizontale
    if(horizontale(pd, dd, field, JCP, JP))
        return true;

    // Verticale
    if(verticale(pd, dd, field, JCP, JP))
        return true;

    // Oblique 1
    if(oblique1(pd, dd, field, JCP, JP))
        return true;

    // Oblique 2
    if(oblique2(pd, dd, field, JCP, JP))
        return true;

    return false;
}

void addJeton(int pd, int dd, char*** field, int* JCP, int JP, char* jeton)
{

    int line = JCP[JP];
    int col = JP-1;

    field[line][col] = jeton;
    JCP[JP] += 1;
    // printf("\nchamp %s ici\n",  field[line][col]);

}

void initColPos(int dd, int** col)
{
    int* M = NULL;

    M = malloc(dd*sizeof(int));
    for(int i = 0; i < dd; i++)
        M[i] = 0;

    *col = M;
}

void Alloc(int pd, int dd, char**** champ)
{
    char*** M = NULL;

    M = malloc(pd*sizeof(char**));

    for(int i = 0; i < pd; i++){
        M[i] = NULL;
        M[i] = malloc(dd*sizeof(char*));
    }
    for(int i = 0; i < pd; i++)
        for(int j = 0; j < dd; j++)
            M[i][j] = " ";

    *champ = M;
}

void showTables(int pd, int dd, char*** fl)
{
    printf("\n\t\tPuissance 4\n\n\n");
    printf("\t  1   2   3   4   5   6   7 \n");
    for(int i = pd-1; i >= 0; i--)
        printf("\t| %s | %s | %s | %s | %s | %s | %s |\n", fl[i][0], fl[i][1], fl[i][2], fl[i][3], fl[i][4], fl[i][5], fl[i][6]);
    printf("\t  _   _   _   _   _   _   _ \n\n");

}

void showP4(int pd, int dd, char*** fl)
{
    printf("\n\t\t §\033[1;31m Game over \033[0m§\n\n\n");
    printf("\t  1   2   3   4   5   6   7 \n");
    for(int i = pd-1; i >= 0; i--)
        printf("\t| %s | %s | %s | %s | %s | %s | %s |\n", fl[i][0], fl[i][1], fl[i][2], fl[i][3], fl[i][4], fl[i][5], fl[i][6]);
    printf("\t  _   _   _   _   _   _   _ \n\n");

}
