/*
 * main.c
 *
 *  Created on: Oct 21, 2013
 *      Author: martin
 */

#include<stdio.h>

int main(){
	int v1[3],t[3],v2[4],i;
	v2[3]=1;
	printf("Ingrese los valores \"x\", \"y\", y \"z\"\n");
	for(i=0;i<3;i++){
		scanf("%d",&v1[i]);
	}
	printf("Ingrese los valores de traslación \"x0\", \"y0\", y \"z0\"\n");
	for(i=0;i<3;i++){
		scanf("%d",&t[i]);
	}
	for(i=0;i<3;i++){
		v2[i]=t[i]+v1[i];
	}
	printf("El vector trasladado es:\n");
	for(i=0;i<4;i++){
		printf("%d\n",v2[i]);
	}
	printf("Dato curioso: La nota del ejercicio 36 es verdadera");
	return 0;
}
