/*
 * main.c
 *
 *  Created on: Oct 23, 2013
 *      Author: martin
 */

#include<stdio.h>
#include<stdlib.h>

int main(){
	int m,n,p,i,j,k;
	int** A,**B,**AB;
	printf("Ingrese la cantidad de filas de la matriz A\n");
	scanf("%d",&m);
	printf("Ingrese la cantidad de columnas de A y filas de B\n");
	scanf("%d",&n);
	printf("Ingrese la cantidad de columnas de B\n");
	scanf("%d",&p);
	A=(int **)calloc(m,sizeof(int *));
	for(i=0;i<m;i++){
		A[i]=(int *)calloc(n,sizeof(int));
	}
	B=(int **)calloc(n,sizeof(int *));
	for(i=0;i<n;i++){
		B[i]=(int *)calloc(p,sizeof(int));
	}
	AB=(int **)calloc(m,sizeof(int *));
	for(i=0;i<m;i++){
		AB[i]=(int *)calloc(p,sizeof(int));
	}
	printf("Inicialización de la matriz A(%dx%d)\n",m,n);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("Ingrese el valor del elemento %d%d \n", (i+1),(j+1));
			scanf("%i", &A[i][j]);
		}
	}
	printf("Inicialización de la matriz B(%dx%d)\n",n,p);
	for(i=0;i<n;i++){
		for(j=0;j<p;j++){
			printf("Ingrese el valor del elemento %d%d \n", (i+1),(j+1));
			scanf("%d", &B[i][j]);
		}
	}
	for(i=0;i<m;i++){
		for(j=0;j<p;j++){
			AB[i][j]=0;
		}
	}
	/*Multiplicación*/
	for(i=0;i<m;i++){
		for(j=0;j<p;j++){
			for(k=0;k<n;k++){
				AB[i][j]=AB[i][j]+A[i][k]*B[k][j];
			}
		}
	}
	/*Show*/
	printf("La matriz AB(%dx%d) es: \n",m,p);
	for(i=0;i<m;i++){
		for(j=0;j<p;j++){
			printf("%d ", AB[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<m;i++){
		free(A[i]);
	}
	free(A);
	for(i=0;i<n;i++){
		free(B[i]);
	}
	free(B);
	for(i=0;i<m;i++){
		free(AB[i]);
	}
	free(AB);
	return 0;
}
