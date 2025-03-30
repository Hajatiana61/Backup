
#include <stdio.h>
#include <stdlib.h>

void getData(int* dim, float*** A, float** B, float** X);
void displayResult(float** A, float* B, float* X, int dim);
void gauss(float* X, float** A, float* B, int dim);
void cleanUp(float* X, float* B, float** A);

int main()
{
    printf("Resolution de A.X = B par le meth. de Gauss\n");

// Entrer des donnes
    int dim = 1;
    float** A=NULL;                 // Adress du matrice problem
    float* B=NULL;                  // Adress du vecteur second membre
    float* X=NULL;                  // Adress du c)vecteur solution
    getData(&dim, &A, &B, &X);

// Calcul: Methode de Gauss
    gauss(X, A, B, dim);

// Sortie des resultats
    displayResult(A, B, X, dim);

// Nettoyage des espaces allouée dynamiquement

    cleanUp(X, B, A);

    return 0;
}
/*--------------------------------------------------------------------------------------------------------------*/


void getData(int* dim, float*** A, float** B, float** X)
{
    printf("voici les donnees \n");
    FILE* fic = NULL;
    fic = fopen("matrice.txt", "r+");
    if(fic==NULL) exit(1);

    fscanf(fic,"%d", dim);

    float* v=NULL; float* s=NULL; float** M=NULL;

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

    *X = v;                                                                 // Je passe v à x

/*--------------------------------------------------------------------------------------------------------------*/

    fclose(fic);
}

void gauss(float* X, float** A, float* B, int dim)
{
    for(int k = 0; k < dim; k++)
    {
        for(int i = k+1; i < dim; i++)
        {
            for(int j = k+1; j < dim; j++)
            {
                A[i][j] = A[i][j] - ((A[i][k]/A[k][k]) * A[k][j]);
            }

            B[i] =  B[i] - ((A[i][k]/A[k][k]) * B[k]);
            A[i][k] = 0;

        }
    }

    float s=0;
    for(int i=dim-1; i>=0; i--)
    {
        s=0;
        for(int j=i+1; j<dim; j++)
            s += A[i][j]*X[j];

        X[i] = (B[i] - s) / A[i][i];

    }
/*
     /// Calcule de Z
    X[2]=B[2]/A[2][2];
    /// Calcule de Y
    X[1]=(B[1]-A[1][2]*X[2]) / A[1][1];
    /// Calcule de X
    X[0]=(B[0]-(A[0][2]*X[2])-(A[0][1]*X[1])) / A[0][0];
*/
}
void displayResult(float** A, float* B, float* X, int dim)
{
    printf("la dimension est %d\n", dim);

    printf("voici le matrice problem:\n");

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++)
            printf("%f  ", A[i][j]);

        printf("\n");
    }

    printf("voici le vecteur du second membre:\n");

    for(int tmp = 0; tmp < dim; tmp++)
        printf("B[%d] = %f\n", tmp, B[tmp]);

    printf("voici le vecteur solution:\n");

    for(int tmp = 0; tmp < dim; tmp++)
        printf("X[%d] = %f\n", tmp, X[tmp]);
}


void cleanUp(float* X, float* B, float** A )
{
    if( X != NULL )
    {
        printf("Je libere X\n");
        free(X);
    }
    if( B != NULL )
    {
        printf("Je libere B\n");
        free(B);
    }

}
