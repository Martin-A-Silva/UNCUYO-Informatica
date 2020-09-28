/*
 * main.c
 *
 *  Created on: Oct 23, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <stdlib.h>


int main(){
	float pot(float x, int n){
		int i;
		float pot=1;
		for(i=0;i<n;i++){
			pot=pot*x;
		}
		return pot;
	}
	int i,n,*arrc;
	float x,x1,x2,dx,r;
	float *arr;
	printf("Ingrese el orden del polinomio:");
	scanf("%d", &n); printf ("\n");
	arr=(float *)calloc(n,sizeof(n));
	arrc=(int *)calloc(n,sizeof(n));
	printf("Ingrese el valor de x1:");
	scanf("%f", &x1);printf("\n");
	x=x1;
	printf("Ingrese el valor de x2:");
	scanf("%f", &x2);printf("\n");
	printf("Ingrese el incremento en x:");
	scanf("%f", &dx);printf("\n");
	for(i=0;i<n;i++){
		printf ("Ingrese el coeficiente c%d:",i);
		scanf ("%d", (arrc+i));printf("\n");
	}
	for(x=x1;x<=x2;x+=dx){
		for(i=0;i<n;i++){
			*(arr+i)=*(arrc+i)*pot(x,i);
		}
		r=0;
		for(i=0;i<n;i++){
			r+=*(arr+i);
		}
		printf("Para x=%f el resultado es: %f\n",x,r);
	}
	free(arr);
	free(arrc);
	return 0;
}
