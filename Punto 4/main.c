/*
 * main.c
 *
 *  Created on: 03/09/2013
 *      Author: usuario
 */

#include <stdio.h>

#define rutina_1

#ifdef rutina_1
	int main(void){
		char a = 'A';
		long b;
		int c;
		float d;
		printf("Ingrese el valor del número mayor\n");
		scanf("%ld", &b);
		printf("Ingrese el valor del número menor\n");
		scanf("%d", &c);
		d = (float)b/c;
		printf("El número %c es %f veces más grande",a,d);
		return 0;
	}
#endif
