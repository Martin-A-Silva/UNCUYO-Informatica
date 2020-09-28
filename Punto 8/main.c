/*
 * main.c
 *
 *  Created on: Sep 25, 2013
 *      Author: martin
 */

#include <stdio.h>

int main(){
	int i,a,b,c,cociente;
	float h,cocientef;
	h=0;
	printf ("Ingrese el valor inicial \"a\":");
	scanf ("%d", &a);
	printf ("Ingrese el valor final \"b\":");
	scanf ("%d", &b);
	printf ("Ingrese el número \"c\":");
	scanf ("%d", &c);
	for (i=a;i<=b;i++){
		cociente=i/c;
		cocientef=(float)i/c;
		if((cocientef-cociente)==0){
			h++;
		}
	}
	i=(int)h;
	printf ("%d", i);
return 0;
}
