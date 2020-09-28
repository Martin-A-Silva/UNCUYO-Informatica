/*
 * main.c
 *
 *  Created on: Oct 14, 2013
 *      Author: martin
 */

#include<stdio.h>

int *pvec(int *a,int *b, int *pv);

int main(){
	int i,a[3],b[3],pv[3];
	printf("Inicialización del vector a(3)\n");
	for(i=1;i<=3;i++){
		printf("Ingrese el elemento a[%d]\n", i);
		scanf("%d", &a[i]);
	}
	printf("Inicialización del vector b(3)\n");
	for(i=1;i<=3;i++){
			printf("Ingrese el elemento b[%d]\n", i);
			scanf("%d", &b[i]);
	}
	pvec(a,b,pv);
	printf("El producto vectorial es:\n");
	for(i=0;i<3;i++){
		printf("%d\n", *(pv+i));
	}
	return 0;
}

int *pvec(int *a,int *b, int *pv){
	*pv=a[2]*b[3]-a[3]*b[2];
	*(pv+1)=a[3]*b[1]-a[1]*b[3];
	*(pv+2)=a[1]*b[2]-a[2]*b[1];
	return pv;
}
