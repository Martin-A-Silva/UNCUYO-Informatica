/*
 * main.c
 *
 *  Created on: Oct 3, 2013
 *      Author: martin
 */

#include<stdio.h>
#define c
#ifdef c
int main(){
	int a,b,i;
	printf ("Ingrese un número entero \n");
	scanf ("%d", &a);
	for(i=0;i!=9;i++){
		b=(a&((1<<(8))>>i));
		if(b!=0){
			b=b/b;
		}
		printf("%d",b);
	}
	printf ("\n");
	return 0;
}
#endif
#ifdef d
int main(){
	int a=2;
	a=(a&(1<<1))/a;
	printf("%d", a);
	return 0;
}
#endif
