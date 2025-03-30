#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void getData(int* dim, float*** A, float** B,float** X, float** Y);
void cleanUp(float* Y, float* X, float* B, float** A);
void display_Inferieur(char* msg, float** tab, int dim);
void display_Superieur(char* msg, float** tab, int dim);
void show_Break(char* msg, float* table, int dim);
void Triangle_Inferieur(float** A, int dim);
void Vecteur_Y(float** A, float* B, float* Y, int dim);
void Vecteur_X(float** A, float* Y, float* X, int dim);
void Transposition(float** A, int dim);
void Cholesky(float** A, float* B, float* X, float* Y,int dim );

int main()
{
    int dim = 0;
    float** A = NULL;          // Adress du matrice problem
    float* B = NULL;           // Adress du second membre
    float* X = NULL;           // Solution du matrice
    float* Y = NULL;           // Soluton sur la maritrice triangulere inferieure


/// Data Enter
    getData(&dim, &A, &B, &X, &Y);

    display_Inferieur("la matrice Problem", A, dim);
/// Resolutions
    Cholesky(A, B, X, Y, dim);

/// Show results
    show_Break("le solution :", X, dim);

// Nettoyage des espaces allouée dynamiquement

    cleanUp(Y, X, B, A);

    return 0;
}
void Cholesky(float** A, float* B, float* X, float* Y, int dim )
{
    Triangle_Inferieur(A, dim);                 /// Dont on trouve la matrice triangulere inferieure
    display_Inferieur("la matrice triangulaire Inferieur", A, dim);

/// Resolution de l'equation A.Y = B
    Vecteur_Y(A, B, Y, dim);                    /// Dont on obtient le vecteur Y
    show_Break("le vecteur Y ", Y, dim);
    /*show_Break("le vecteur Y", Y, dim);*/
/// Transposée de A
    Transposition(A, dim);
    display_Superieur(" la matrice triangle superieur ",A, dim);

/// Resolution de l'equation A'.X = Y

    Vecteur_X(A, Y, X, dim);

}

void getData(int* dim, float*** A, float** B,float** X, float** Y)
{
    //printf("voici les donnees \n");
    FILE* fic = NULL;
    fic = fopen("data.txt", "r+");
    if(fic==NULL) exit(1);

    fscanf(fic,"%d", dim);

/*--------------------------------------------------------------------------------------------------------------*/

    float* v=NULL; float* s=NULL; float** M=NULL;float* m=NULL;

/*--------------------------------------------------------------------------------------------------------------*/
    M = malloc(*dim*sizeof(float*));
    for(int tmp = 0; tmp < *dim; tmp++)
    {
        M[tmp]=NULL;
        M[tmp] = malloc(*dim*sizeof(float));
        if( M[tmp] == NULL) exit(1);
    }

    for(int i = 0; i < *dim; i++)
        for(int j = 0; j < *dim; j++)
            fscanf(fic,"%f", &M[i][j]);

    *A = M;

/*--------------------------------------------------------------------------------------------------------------*/
    s = malloc(*dim*sizeof(float));
    if(s == NULL) exit(1);

    for(int tmp = 0; tmp < *dim; tmp ++) fscanf(fic, "%f", &s[tmp]);

    *B = s;                                                                 // Je passe s à b
/*--------------------------------------------------------------------------------------------------------------*/
    v = malloc(*dim*sizeof(float));
    if(v == NULL) exit(1);

    for(int tmp = 0; tmp < *dim; tmp ++) v[tmp] = 0;

    *X = v;*Y = m;                                                                 // Je passe v à x et à y

    m = malloc(*dim*sizeof(float));
    if(v == NULL) exit(1);

    for(int tmp = 0; tmp < *dim; tmp ++) m[tmp] = 0;

    *Y = m;
/*--------------------------------------------------------------------------------------------------------------*/


    fclose(fic);
}

void cleanUp(float* Y, float* X, float* B, float** A )
{
    if( Y != NULL )
    {
        //printf("Je libere Y\n");
        free(Y);
    }

    if( X != NULL )
    {
        //printf("Je libere X\n");
        free(X);
    }
    if( B != NULL )
    {
        //printf("Je libere B\n");
        free(B);
    }
     if( A != NULL )
    {
        //printf("Je libere A\n");
        free(A);
    }


}
void show_Break(char* msg, float* table, int dim)
{
    printf("\nVoici %s: \n", msg);
    for(int tmp = 0; tmp < dim; tmp++)
        printf("Vecteur[%d] = %f\n", tmp, table[tmp]);

}
void display_Superieur(char* msg, float** tab, int dim)
{

    printf("\nVoici %s:\n", msg);

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim ; j++)
            printf("%f  ", tab[i][j]);

        printf("\n");
    }

}

void display_Inferieur(char* msg, float** tab, int dim)
{

    printf("\nVoici %s:\n", msg);

    for(int i = 0; i < dim; i++){
        for(int j = 0; j <= i; j++)
            printf("%f  ", tab[i][j]);

        printf("\n");
    }

}
void Triangle_Inferieur(float** A, int dim)
{
    for(int i=0; i < dim; i++)
    {
        for(int j=0; j < i; j++)
        {
            float tmp=0;
            for(int k=0; k < j; k++)            // Sigma 1
                tmp += A[i][k]*A[j][k];

            A[i][j] = (1/A[j][j]) * (A[i][j] - tmp);
        }
        float tmp = 0;
        for(int k=0; k < i; k++)                // Sigma 2
            tmp += A[i][k]*A[i][k];


        A[i][i] = sqrt(A[i][i] - tmp);

        for(int j=i+1; j < dim; j++)
            A[i][j] = 0;

    }

}

void Vecteur_Y(float** A, float* B, float* Y, int dim)
{
    float s = 0;
    for(int i = 0; i < dim; i++)
    {
        s=0;
        for(int j = i - 1; j >= 0; j--)
            s += A[i][j]* Y[j];

        Y[i] = (B[i] - s) / A[i][i];

    }

}
void Vecteur_X(float** A, float* Y, float* X, int dim)
{
    float s = 0;
    for(int i = dim - 1; i >= 0; i--)
    {
        s=0;
        for(int j = i + 1; j < dim; j++)
            s += A[i][j]* X[j];

        X[i] = (Y[i] - s) / A[i][i];

    }
}

void Transposition(float** A, int dim)
{
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < i; j++)
        {
            A[j][i] = A[i][j];
            A[i][j] = 0;

        }

}





















