
#include <stdio.h>
#include <stdlib.h>

void getData(int* dim, float*** A, float** B, float** X, int** Piv );
void displayResult(char* msg, float** A, int dim);
void gauss(float* X, float** A, float* B,int* Piv, int dim);
void cleanUp(float* X, float* B, float** A);
float High_Pivot(float** A,int* Piv, int dim,int k);
void show_Break(char* msg, float* table, int dim, int* Piv);

int main()
{
    printf("Resolution de A.X = B par le methode de Gauss\n");

// Entrer des donnes
    int dim = 1;
    float** A=NULL;                 // Adress du matrice problem
    float* B=NULL;                  // Adress du vecteur second membre
    float* X=NULL;                  // Adress du vecteur solution
    int* Piv=NULL;                  // Adress du pivot
    getData(&dim, &A, &B, &X, &Piv);

    displayResult("la matrice problem",A, dim);
    show_Break("le vecteur second", B, dim, Piv);
// Calcul: Methode de Gauss
    gauss(X, A, B,Piv, dim);
    displayResult("la matrice problem",A, dim);

// Sortie des resultats
    show_Break(" la solution ",X, dim, Piv);

// Nettoyage des espaces allouée dynamiquement

    cleanUp(X, B, A);

    return 0;
}
/*--------------------------------------------------------------------------------------------------------------*/


void getData(int* dim, float*** A, float** B, float** X, int** Piv)
{
    //printf("voici les donnees \n");
    FILE* fic = NULL;
    fic = fopen("matrice.txt", "r+");
    if(fic==NULL) exit(1);

    fscanf(fic,"%d", dim);

    float* v=NULL; float* s=NULL; float** M=NULL; int* nb=NULL;

    nb = malloc(*dim*sizeof(int));
    if(nb == NULL) exit(1);

    for(int tmp = 0; tmp < *dim; tmp++) nb[tmp] = tmp;

    *Piv = nb;
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

void gauss(float* X, float** A, float* B,int* Piv, int dim)
{
/*--------------------------------------------------------------------------------------------------------------*/
    float pos = 0;
	int tmp = 0;
	int lpiv = 0;

   // show_Break("",Piv, dim);
    for(int k = 0; k < dim-1 ; k++)                 // determine le pivot
    {

        pos =  High_Pivot(A, Piv,dim, k);
        for(int i = k;i < dim;i++){
			if(A[Piv[i]][k] == pos){
				lpiv = i;
				break;
			}
		}
        	tmp = Piv[k];
 	      	Piv[k] = Piv[lpiv];
        	Piv[lpiv] = tmp;

        printf("\nLe Rang Pivots : %d %d %d %d\n", Piv[0], Piv[1], Piv[2], Piv[3]);
        for(int i = k+1; i < dim; i++)              // determine la ligne
        {
            for(int j = k+1; j < dim; j++)          // determine la collone
            {
                A[Piv[i]][j] = A[Piv[i]][j] - ((A[Piv[i]][k]/A[Piv[k]][k]) * A[Piv[k]][j]);
            }

            B[Piv[i]] =  B[Piv[i]] - ((A[Piv[i]][k]/A[Piv[k]][k]) * B[Piv[k]]);
            A[Piv[i]][k] = 0;

        }
        displayResult("la matrice Apres triangularisation", A, dim);
        show_Break("le vecteur second", B, dim, Piv);
    }

/*--------------------------------------------------------------------------------------------------------------*/
/// Resolution

    float s = 0;
    for(int i = dim - 1; i >=0; i--)
    {
        s=0;
        for(int j = i + 1; j < dim; j++)
            s += A[Piv[i]][j]* X[Piv[j]];

        X[Piv[i]] = (B[Piv[i]] - s) / A[Piv[i]][i];

    }
/*--------------------------------------------------------------------------------------------------------------*/

/*
     /// Calcule de Z
    X[2]=B[2]/A[2][2];
    /// Calcule de Y
    X[1]=(B[1]-A[1][2]*X[2]) / A[1][1];
    /// Calcule de X
    X[0]=(B[0]-(A[0][2]*X[2])-(A[0][1]*X[1])) / A[0][0];
*/
}
void displayResult(char* msg, float** A,  int dim)
{

    printf("\nVoici %s\n", msg);

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++)
            printf("%f  ", A[i][j]);

        printf("\n");
    }

}
void cleanUp(float* X, float* B, float** A )
{
    if( X != NULL )
    {
        //printf("Je libere X\n");
        free(X);
    }
    if( B != NULL )
    {
       // printf("Je libere B\n");
        free(B);
    }
     if( A != NULL )
    {
       // printf("Je libere B\n");
        free(A);
    }
}

/*void High_Pivot(float** A,int* Piv, int dim, int k)
{

    printf(" Pivot : %d %d %d\n\n", Piv[0], Piv[1], Piv[2]);
    for(int i = 0; i < dim; i++)
    {
        for(int j=i+1; j < dim; j++)
        {
            if(A[i][k] < A[j][k])
            {
                int tmp = 0;
                tmp = Piv[i];
                Piv[i] = Piv[j];
                Piv[j] = tmp;
            }
            else
                continue;
        }
    }
    printf(" Pivot : %d %d %d\n\n", Piv[0], Piv[1], Piv[2]);
}
*/
float High_Pivot(float** A,int* Piv, int dim, int k)
{

   // printf(" Pivot : %d %d %d\n\n", Piv[0], Piv[1], Piv[2]);
    float tmp = A[Piv[k]][k];
	float tmp1;
	for(int i = k+1;i < dim;i++){;
		tmp1 = A[Piv[i]][k];
		if(abs(tmp1) > abs(tmp)){
			tmp = tmp1;
		}
	}
//	printf("T : %f\n",tmp);
	return tmp;
  //  printf(" Pivot : %d %d %d\n\n", Piv[0], Piv[1], Piv[2]);
}

void show_Break(char* msg, float* table, int dim, int* Piv)
{
    printf("\nVoici %s: \n", msg);
    for(int tmp = 0; tmp < dim; tmp++)
        printf("Vecteur[%d] = %f\n", tmp, table[Piv[tmp]]);

}
