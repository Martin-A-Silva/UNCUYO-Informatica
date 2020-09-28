/*
 * main.c
 *
 *  Created on: Oct 7, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int N;

int *funcion(){
	srand(time(0));
	printf("Ingrese el tamaño del vector \n");
	scanf ("%d", &N);
	int i, *arr;
	arr=(int *)calloc(N,sizeof(int));
	printf ("Impresión por función \n");
	for(i=0;i<N;i++){
		*(arr+i)=rand()/10000;
		printf ("%d \n", *(arr+i));
	}
	return arr;
}

int pares(int *arr){
	int i;
	printf("Impresión por punto 21 \n");
	for(i=0;i<N;i++){
		if(((*(arr+i))%2)==0){
			printf ("%d\n", *(arr+i));
		}
	}
	return 0;
}

int impares(int *arr){
	printf("Impresión por Punto 22\n");
	int i, mimp=0,*arrimp;
	for(i=0;i<N;i++){
		if(((*(arr+i))%2)==1){
			mimp++;
		}
	}
	arrimp=(int *)calloc(mimp,sizeof(int));
	for(i=0;i<N;i++){
		if(((*(arr+i))%2)==1){
			*(arrimp+i)=*(arr+i);
			printf ("%d \n", *(arrimp+i));
		}
	}
	free(arrimp);
	return 0;
}

int subimpar(int *arr){
	int i,v=0;
	for(i=1;i<N;i+=2){
		v+=*(arr+i);
	}
	printf ("Impresión por punto 23 \nSumatoria de elementos de subíndice impar: %d \n", v);
	return 0;
}

int promedio(int *arr){
	int i,t=0;
	float p;
	for(i=0;i<N;i++){
		t+=*(arr+i);
	}
	p=(float)t/N;
	printf ("Impresión por punto 24\nPromedio de los elementos: %f \n", p);
	return 0;
}

int menor(int *arr){
	int i,m=*arr;
	for(i=1;i<N;i++){
		if(*(arr+i)<m){
			m=*(arr+i);
		}
	}
	printf ("Impresión por punto 25\nEl menor de todos los elementos es: %d \n", m);
	return 0;
}

int main(){
	int i,*arr;
	/* Punto 20*/
	arr=funcion();
	/* Punto 21 */
	pares(arr);
	/* Punto 22 */
	impares(arr);
	/* Punto 23 */
	subimpar(arr);
	/* Punto 24 */
	promedio(arr);
	/* Punto 25 */
	menor(arr);
	free(arr);
	printf("Gracias por confiar en este producto, se deducirán 500 dólares de su cuenta bancaria");
	return 0;
}
