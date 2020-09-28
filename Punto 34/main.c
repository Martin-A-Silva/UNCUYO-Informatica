/*
 * main.c
 *
 *  Created on: Oct 21, 2013
 *      Author: martin
 */

#include<stdio.h>

int main(){
	int v1[3],s[3],v2[4],i;
	v2[3]=1;
	printf("Ingrese los valores \"x\", \"y\", y \"z\"\n");
	for(i=0;i<3;i++){
		scanf("%d",&v1[i]);
	}
	printf("Ingrese los factores de escala \"sx\", \"sy\", y \"sz\"\n");
	for(i=0;i<3;i++){
		scanf("%d",&s[i]);
	}
	for(i=0;i<3;i++){
		v2[i]=s[i]*v1[i];
	}
	printf("El vector escalado es:\n");
	for(i=0;i<4;i++){
		printf("%d\n",v2[i]);
	}
	printf("NOTA: Ningún programador fue herido durante la elaboración de este programa.");
	return 0;
}
