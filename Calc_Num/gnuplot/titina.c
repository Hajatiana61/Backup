#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float **alocTwodim(float **array,int size);
void getDataF(FILE *donne,float **matrice,int size,int dim);
void printTabTwoDim(float **tab,int size,int dim);
void plot(FILE *gp,int size);
void plotMorceau(FILE *gp,float **tab,int size);
void plotLagrange(FILE *gp,float **tab,int size);
float *allocOneDime(float *tab,int size);
float *getLambda(float **md,float *lambda,int size);
void printTabOnedim(float *tab,int size);
float *getp(float **md,float *p,int size);
float *getScalY(float **md,float *y,int size);
float **getX(float **x,float *p,float *lambda,int size);
float **triangularisationSup(float **matrice,int size);
float *solutionSuperieur(float **array,float *scalar,float *answer,int taille);
float **transposer(float **matrice,int taille);
float *solutionSystem(float **array,float *scalar,float *answer,int taille);
void plotSpline(FILE *gp,float **tab,float *s,int size);
int main(){
	int dim = 2;
	int size = 7;
	FILE *donne = fopen("interpelation.txt","r");
	if(donne == NULL){
		exit(1);
	}
	FILE *gp = popen("gnuplot -persist","w");
	if(gp == NULL){
		exit(1);
	}

	float **md = NULL;
	md = alocTwodim(md,size);
	getDataF(donne,md,size,dim);

	int sizeL = size - 2;
	int sizeM = size - 1;
	float *lambda = NULL;
	float *p = NULL;
	float *y = NULL;
	float **x = NULL;
	float **sx = NULL;
	float **tx = NULL;
	float *x1 = NULL;
	float *s = NULL;

	x = alocTwodim(x,sizeM);
	sx = alocTwodim(sx,sizeM);
	tx = alocTwodim(tx,sizeM);
	x1 = allocOneDime(x1,sizeM);
	s = allocOneDime(s,sizeM);
	lambda = allocOneDime(lambda,sizeL);
	lambda = getLambda(md,lambda,sizeL);
	p = allocOneDime(p,sizeL);
	p = getp(md,p,sizeL);
	y = allocOneDime(y,sizeL);
	y = getScalY(md,y,sizeL);
	x = getX(x,p,lambda,sizeM);
	sx = triangularisationSup(x,sizeM);
//	printTabTwoDim(x,sizeM,sizeM);
	x1 = solutionSuperieur(sx,y,x1,sizeM);
	tx = transposer(sx,sizeM);
	s = solutionSystem(tx,x1,s,sizeM);
//	printTabOnedim(s,sizeM);
//	printTabOnedim(lambda,sizeL);
//	printf("--\n");
/*
	printTabOnedim(p,sizeL);
	printf("--\n");
	printTabOnedim(y,sizeL);
*/
	plotMorceau(gp,md,size);
	plotLagrange(gp,md,size);
	plotSpline(gp,md,s,sizeM);
	plot(gp,size);

	return 0;
}
void plotSpline(FILE *gp,float **tab,float *s,int size){
    float d = 0;
    float a = 0;
    float b = 0;
    float s2 = 0;
    float s12 = 0;
    for(int i = 0; i <= size -1; i++){
        d = tab[i+1][0] - tab[i][0];
        s2 = (s[i]*s[i]);
        s12 = (s[i+1]*s[i+1]);
        a = (tab[i][1]/d) - ( s2*d/6 );
        b = (tab[i+1][1]/d) - ( s12*d/6 );
        fprintf(gp, "S%d(x)= (x >= %f && x <= %f) ? (((1/(6*%f))*(%f*(%f-x)*(%f-x)*(%f-x) + %f*(x-%f)*(x-%f)) + %f*(%f-x) + %f*(x-%f))) : 1/0\n",i,tab[i][0],tab[i+1][0],d,s2,tab[i+1][0],tab[i+1][0],tab[i+1][0],s12,tab[i][0],tab[i][0],a,tab[i+1][0],b,tab[i][0]);
    }
/*
	d = tab[size][0] - tab[size-1][0];
	a = (tab[size-1][1]/d);
	b = (tab[size][1]/d);
	fprintf(gp, "S%d(x)= (x >= %f && x <= %f) ? (((1/(6*%f))+ %f*(%f-x) + %f*(x-%f))) : 1/0\n",size-1,tab[size-1][0],tab[size][0],d,a,tab[size][0],b,tab[size-1][0]);
*/
}
float *solutionSystem(float **array,float *scalar,float *answer,int taille){
        float somme = 0;
        answer[taille - 1] = scalar[taille - 1] / array[taille - 1][taille - 1];
        for(int i = taille - 2;i >= 0;i--){
                for(int j = i+1;j < taille;j++){
                        somme = array[i][j]*answer[j] + somme;
                }
                answer[i] = (1/array[i][i])*(scalar[i] - somme);
                somme = 0;
        }
        return answer;
}
float **transposer(float **matrice,int taille){
	float **tmatrice = NULL;
	tmatrice = alocTwodim(tmatrice,taille);
	for(int i = 0;i < taille;i++){
		for(int j = 0;j < taille;j++){
			tmatrice[i][j] = matrice[j][i];
		}
	}
	return tmatrice;
}
float *solutionSuperieur(float **array,float *scalar,float *answer,int taille){
        float somme = 0;
        answer[0] = scalar[0] / array[0][0];
        for(int i = 1;i < taille ;i++){
                for(int j = i-1;j >= 0;j--){
                        somme = array[i][j]*answer[j] + somme;
                }
//		printf("%f\n",somme);
                answer[i] = (1/array[i][i])*(scalar[i] - somme);
                somme = 0;
        }
        return answer;
}
float **triangularisationSup(float **matrice,int size){
	float **mat1 = NULL;
        mat1 = alocTwodim(mat1,size);
	float s1 = 0;
	float s2 = 0;
	for(int i = 0;i < size;i++){
		s2 = 0;
		for(int j = 0;j < i ;j++){
			s1 = 0;
			for(int k = 0;k < j ;k++){
//				printf("%f * %f + %f\n",mat1[i][k],mat1[j][k],s1);
				s1 = mat1[i][k] * mat1[j][k] + s1;
			}
//			printf("(%f - %f) / %f = %f\n",matrice[i][j],s1,mat1[j][j],(matrice[i][j] - s1)/mat1[j][j]);
			mat1[i][j] = (matrice[i][j] - s1)/mat1[j][j];
		}
		for(int k = 0;k < i ;k++){
			s2 = mat1[i][k] * mat1[i][k] + s2;
		}
		mat1[i][i] = sqrt(matrice[i][i] - s2);
	}
	return mat1;
}
float **getX(float **x,float *p,float *lambda,int size){
	for(int i = 0;i < size ;i++){
		for(int j = 0;j < size;j++){
			x[i][j] = 0;
		}
	}

	for(int i = 0;i < size;i++){
		x[i][i] = 2;
	}

	for(int i = 0;i < size - 1;i++){
		x[i][i+1] = lambda[i];
	}
	for(int i = 0;i < size - 1;i++){
		x[i+1][i] = p[i];
	}
	return x;
}
float *getScalY(float **md,float *y,int size){
	float d = 0;
	float dS = 0;
	for(int i = 1;i <= size;i++){
		d = md[i+1][0] - md[i][0];
		dS = md[i][0] - md[i-1][0];
		y[i-1] = (6/( dS + d)) * ( (md[i][1] - md[i-1][1]/d) - (md[i-1][1] - md[i][1]/dS) );
	}
	return y;
}
float *getp(float **md,float *p,int size){
	for(int i = 1;i <= size;i++){
		p[i-1] = (md[i][0] - md[i-1][0]) / (md[i][0] - md[i-1][0] + md[i+1][0] - md[i][0]);
	}
	return p;
}
void printTabOnedim(float *tab,int size){
	for(int i = 0;i < size;i++){
		printf("%f\n",tab[i]);
	}
}
float *getLambda(float **md,float *lambda,int size){
	for(int i = 1;i <= size;i++){
		lambda[i-1] = (md[i+1][0] - md[i][0]) / (md[i][0] - md[i-1][0] + md[i+1][0] - md[i][0]);
	}
	return lambda;
}
float *allocOneDime(float *tab,int size){
        tab = (float*)malloc(sizeof(float) * size);
        return tab;
}
void plotLagrange(FILE *gp,float **tab,int size){
	fprintf(gp, "P(x)=0");
	for(int j = 0;j < size;j++){
		fprintf(gp, "+ %f",tab[j][1]);
		for(int k = 0;k < size;k++){
			if(k == j){
				continue;
			}
			fprintf(gp," * (x - %f)/(%f - %f)",tab[k][0],tab[j][0],tab[k][0]);
		}
	}
	fprintf(gp, "\n");
}
void plotMorceau(FILE *gp,float **tab,int size){
    float d = 0;
    for(int i = 0; i < size - 1; i++){
        d = (tab[i+1][1] - tab[i][1]) / (tab[i+1][0] - tab[i][0]);
        fprintf(gp, "f%d(x)= (x >= %f && x <= %f) ? (%f + %f * (x - %f)) : 1/0\n",i,tab[i][0],tab[i+1][0],tab[i][1],d,tab[i][0]);
    }
}
void plot(FILE *gp,int size){
		fprintf(gp,"set xrange[0:8] \n");
		fprintf(gp,"set yrange[-20:20] \n");
		fprintf(gp, "set style line 1 linecolor rgb 'red' linetype 1 linewidth 2\n");
		fprintf(gp, "set style line 2 linecolor rgb 'black' linetype 1 linewidth 2\n");
		fprintf(gp,"plot P(x),'interpelation.txt'");
		for(int i = 0; i < size - 1; i++){
			 fprintf(gp, ", f%d(x) with lines linestyle 1 notitle", i);
		}
		for(int i = 0; i < size-1; i++){
			 fprintf(gp, ", S%d(x) with lines linestyle 2 notitle", i);
		}
		fprintf(gp, "\n");
		fflush(gp);
		pclose(gp);
}
void printTabTwoDim(float **tab,int size,int dim){
	for(int i = 0;i < size;i++){
		for(int j = 0;j < dim;j++){
			printf("%f\t",tab[i][j]);
		}
		printf("\n");
	}
}
void getDataF(FILE *donne,float **matrice,int size,int dim){
	float x = 0;
	for(int i = 0;i < size;i++){
		for(int j = 0;j < dim;j++){
			fscanf(donne,"%f",&x);
			matrice[i][j] = x;
		}
	}
}
float **alocTwodim(float **array,int size){
	array = (float**)malloc(sizeof(float*) * size);
	for(int i = 0;i < size;i++){
		for(int j = 0;j < size;j++){
			*(array + i) = NULL;
			*(array + i) = (float*)malloc(sizeof(float) * size);
		}
	}
	return array;
}
