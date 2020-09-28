/*
 * main.c
 *
 *  Created on: 01/10/2013
 *      Author: usuario
 */

#include <stdio.h>

int main(void){
	int a,b,c,d,e;
	printf("Ingrese los valores en orden descendiente y al final el valor \"e\" \n");
	scanf ("%d %d %d %d %d", &a,&b,&c,&d,&e);
	if (a>=e&&e>=b){
		printf("%d => %d => %d", b,e,a);
	}
	else if (b>=e&&e>=c){
		printf("%d => %d => %d", c,e,b);
	}
	else if (c>=e&&e>=d){
			printf("%d => %d => %d", d,e,c);
	}
	else{
		printf ("El valor \"e\" no se encuentra en el intervalo\n");
	}
	return 0;
}
