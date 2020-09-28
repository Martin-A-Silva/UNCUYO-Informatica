/*
 * main.c
 *
 *  Created on: Oct 14, 2013
 *      Author: martin
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int m,n;

int ej32(int A[m][n]){
	int i,j;
	srand((time(NULL)));
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if((i+j)%2==1){
				A[i][j]=rand()/100000;
			}
			else{
				A[i][j]=0;
			}
		}
	}
	printf("La matriz A es:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	return A;
}

int ej33(int A[m][n]){
	int i,j,AT[n][m];
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			AT[i][j]=A[j][i];
		}
	}
	printf("\nLa transpuesta de la matriz A es:\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d ", AT[i][j]);
		}
		printf("\n");
	}
	printf("Sepa disculpar las borrachas estructuras de las matrices. Anoche hubo fiesta matricial :D");
	return 0;
}

int main(){
	printf("Ingrese la cantidad de filas de la matriz\n");
	scanf("%d", &m);
	printf("Ingrese la cantidad de columnas de la matriz\n");
	scanf("%d", &n);
	int A[m][n];
	ej32(A);
	ej33(A);
	return 0;
}
