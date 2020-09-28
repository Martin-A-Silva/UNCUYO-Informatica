/*
 * main.c
 *
 *  Created on: Oct 14, 2013
 *      Author: martin
 */

#include<stdio.h>

int main(){
	int m=2,n=3,p=2,i,j,k;
	int A[m][n],B[n][p],AB[m][p];
	printf("Inicialización de la matriz A(2x3)\n");
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			printf("Ingrese el valor del elemento %d%d \n", i,j);
			scanf("%i", &A[i][j]);
		}
	}
	printf("Inicialización de la matriz B(3x2)\n");
	for(i=1;i<=n;i++){
		for(j=1;j<=p;j++){
			printf("Ingrese el valor del elemento %d%d \n", i,j);
			scanf("%d", &B[i][j]);
		}
	}
	for(i=1;i<=m;i++){
		for(j=1;j<=p;j++){
			AB[i][j]=0;
		}
	}
	/*Multiplicación*/
	for(i=1;i<=m;i++){
		for(j=1;j<=p;j++){
			for(k=1;k<=n;k++){
				AB[i][j]=AB[i][j]+A[i][k]*B[k][j];
			}
		}
	}
	/*Show*/
	printf("La matriz AB(2x2) es: \n");
	for(i=1;i<=m;i++){
		for(j=1;j<=p;j++){
			printf("%d ", AB[i][j]);
		}
		printf("\n");
	}
	return 0;
}
