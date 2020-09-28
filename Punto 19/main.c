/*
 * main.c
 *
 *  Created on: Oct 5, 2013
 *      Author: martin
 */

#include <stdio.h>

void duplicar(int *v){
	*v*=2;
}
int main(){
	int a=2;
	printf ("Ingrese el valor de la variable a \n");
	scanf("%d",&a);
	duplicar(&a);
	printf ("%d", a);
	return 0;
}
