/*
 * main.c
 *
 *  Created on: Oct 7, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <stdlib.h>


int main(){
	int i,n,c,x;
	printf("Ingrese el orden del polinomio:");
	scanf("%d", &n); printf ("\n");
	int pot(int x, int n){
		int i,pot=1;
		for(i=0;i<n;i++){
			pot=pot*x;
		}
		return pot;
	}
	int *arr;
	arr=(int *)calloc(n,sizeof(n));
	printf("Ingrese el valor de x:");
	scanf("%d", &x);printf("\n");
	for(i=0;i<n;i++){
		printf ("Ingrese el coeficiente c%d:",i);
		scanf ("%d", &c);printf("\n");
		*(arr+i)=c*pot(x,i);
	}
	x=0;
	for(i=0;i<n;i++){
		x+=*(arr+i);
	}
	printf ("El resultado de la función es: %d\nSi el resultado es incorrecto, llame al 0-800-666-MICRO$OFT y por un módico precio le arreglamos el programa.\nGracias por confiar en nosotros.", x);
	free(arr);
	return 0;
}
