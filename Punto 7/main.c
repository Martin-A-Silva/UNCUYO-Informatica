/*
 * main.c
 *
 *  Created on: 01/10/2013
 *      Author: usuario
 */

#include <stdio.h>

int main(void){
	int a,b;
	printf ("Ingrese el valor del número \n");
	scanf ("%d", &a);
	b = a*(a-1);
	a--;
	do{
		a--;
		b = b*a;
	}while ((a)>1);
	printf("El factorial es: %d", b );
	return 0;
}
