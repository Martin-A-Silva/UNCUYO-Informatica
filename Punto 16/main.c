/*
 * main.c
 *
 *  Created on: Oct 4, 2013
 *      Author: martin
 */

#include <stdio.h>

int main(){
	int a,b,c;
	int funcion(int a,int b,int c,float x){
		float funcion= 1.0;
		funcion=a*x*x+b*x+c;
		return funcion;
	}
	float r,x,x1,x2,delta;
	printf ("Ingrese los argumentos \n a:");
	scanf ("%d", &a);
	printf ("\n b:");
	scanf ("%d", &b);
	printf ("\n c:");
	scanf ("%d", &c);
	printf ("\n Ingrese el valor de x1:");
	scanf ("%f", &x1);
	printf ("\n Ingrese el valor de x2:");
	scanf ("%f", &x2);
	printf ("\n Ingrese el valor de delta:");
	scanf ("%f", &delta);
	printf ("Los resultados son: \n");
	for(x=x1;x<x2;x=x+delta){
		r=funcion(a,b,c,x);
		printf ("Para x=%f es %f \n",x,r);
	}
	return 0;
}
