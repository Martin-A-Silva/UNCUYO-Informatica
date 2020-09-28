/*
 * main.c
 *
 *  Created on: 22/10/2013
 *      Author: usuario
 */

#include<stdio.h>
#include<string.h>

int main(){
	char A[100],B[100];
	int i,n;
	printf("Ingrese la cadena\n");
	scanf("%s",&A[0]);
	n=strlen(A);
	for(i=0;i<n;i++){
		B[i]=A[n-1-i];
	}
	B[n]='\0';
	printf("La cadena invertida es:\n");
	for(i=0;i<n;i++){
		printf("%c", B[i]);
	}
	printf("\nAhora en la versión 1.5 es más prolijo y sí se por qué funciona :D");
	return 0;
}
