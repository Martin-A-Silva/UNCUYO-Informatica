/*
 * main.c
 *
 *  Created on: Oct 4, 2013
 *      Author: martin
 */

#include <stdio.h>

int main(){
	int a,b,c,x;
	int funcion(int a,int b,int c,int x){
		int funcion= 1;
		funcion=a*x*x+b*x+c;
		return funcion;
	}
	printf ("Ingrese los argumentos \n a:");
	scanf ("%d", &a);
	printf ("\n b:");
	scanf ("%d", &b);
	printf ("\n c:");
	scanf ("%d", &c);
	printf ("\n Ingrese el valor de x:");
	scanf ("%d", &x);
	x=funcion(a,b,c,x);
	printf ("\n El resultado de la funcion es %d", x);
	return 0;
}
