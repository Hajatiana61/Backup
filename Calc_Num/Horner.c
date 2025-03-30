#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 4

void setValue(int* board, int note);
int CalcHorner(int X, int* board, int note);

int main()
{
    printf("+++  Shemas d'horner  +++\n");
    printf("\nOn a la forme P(X) = anX^(n) + a(n-1)X^(n-1) + ... + a1X^(1) + a0\n");

    /// Pour n = 4, P(X) = (((a4X + a3)X + a2)X + a1)X + a0
    int X = 2; int Answer;
    int* tab = malloc(sizeof(int)*(n+1));

    setValue(tab,n);
    printf(" Pour X = %d\n" , X);

    Answer = CalcHorner(X, tab, n);
    return 0;
}


void setValue(int* board, int note)
{
    printf("    Entrez les valeurs:\n");

    for(int tmp = 0; tmp < (n + 1); tmp ++ )
    {
        printf("a%d = ", tmp);
        scanf("%d", (board+tmp));

    }


}
int CalcHorner(int X, int* board, int note)
{
    int result;
    for(int tmp = n; tmp <= 0; tmp++ )
    {
        result = board[tmp] ;

    }
     return ;

}
