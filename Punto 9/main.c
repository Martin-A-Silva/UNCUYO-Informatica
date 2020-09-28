/*
 * main.c
 *
 *  Created on: Oct 3, 2013
 *      Author: martin
 */

#include<stdio.h>

int main(){
	int i,j,k;
	j=0;
	k=0;
	printf ("Ingrese el valor de \"i\":");
	scanf("%d", &i);
	for(j=0;j!=(i+1);j++){
		k=k+j;
	}
	printf ("El resultado de la función es: %d", k);
	return 0;
}
