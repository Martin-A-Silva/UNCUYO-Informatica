/*
 * main.c
 *
 *  Created on: Oct 5, 2013
 *      Author: martin
 */

#include <stdio.h>

int factorial(int n){
	int factorial = 1;
	int i;
	for(i=1;i<=n;i++){
		factorial=factorial*i;
	}
	return factorial;
}
int main(){
	int a;
	printf ("Ingrese el valor de \"a\":");
	scanf ("%d", &a);
	printf ("\n");
	a=factorial(a);
	printf ("El factorial de \"a\" es: %d", a);
	return 0;
}
