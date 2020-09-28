/*
 * main.c
 *
 *  Created on: Oct 4, 2013
 *      Author: martin
 */

#include <stdio.h>

int main(){
	int a,b,c;
	printf ("Ingrese el valor de a:");
	scanf ("%d", &a); printf("\n");
	printf ("Ingrese el valor de b:");
	scanf ("%d", &b); printf("\n");
	c=a&b;
	printf ("El número que contiene sólo los bits que son 1 en ambos números es %d \n", c);
	c=a|b;
	printf ("El número que contiene sólo los bits que son 1 en alguno de los números es %d \n", c);
	c=a^b;
	printf ("El número que contiene sólo los bits que son distintos en ambos números es %d \n", c);
	return 0;
}
