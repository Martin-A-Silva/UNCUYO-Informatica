/*
 * main.c
 *
 *  Created on: Oct 14, 2013
 *      Author: martin
 */

#include <stdio.h>

int main(){
	int n,i,p=0;
	printf("Ingrese el tamaño de los vectores");
	scanf("%d", &n);
	int a[n],b[n];
	printf("Inicialización del vector a\n");
	for(i=1;i<=n;i++){
		printf("Ingrese el valor del elemento a[%d]\n", i);
		scanf("%d", &a[i]);
	}
	printf("Inicialización del vector b\n");
	for(i=1;i<=n;i++){
			printf("Ingrese el valor del elemento b[%d]\n", i);
			scanf("%d", &b[i]);
	}
	for(i=1;i<=n;i++){
		p=p+a[i]*b[i];
	}
	printf("El producto escalar es: %d \nNOTA: Este programa funciona mejor en computadoras cuánticas", p);
	return 0;
}
