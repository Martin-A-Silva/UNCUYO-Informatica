/*
 * main.c
 *
 *  Created on: Oct 25, 2013
 *      Author: martin
 */

#include<stdio.h>
#include<stdlib.h>

struct vector{
	int x;
	int y;
	int z;
};
int pvec(struct vector *a,struct vector *b,struct vector *pv);

int main(){

	struct vector *a,*b,*pv;
	/*Vector a*/
	a=(struct vector *)malloc(sizeof(struct vector));
	printf("Inicialización del vector a(3)\n");
	printf("Ingrese el elemento a[1]\n");
	scanf("%d", &(a->x));
	printf("Ingrese el elemento a[2]\n");
	scanf("%d", &(a->y));
	printf("Ingrese el elemento a[3]\n");
	scanf("%d", &(a->z));
	/*Vector b*/
	b=(struct vector *)malloc(sizeof(struct vector));
	printf("Inicialización del vector b(3)\n");
	printf("Ingrese el elemento b[1]\n");
	scanf("%d", &(b->x));
	printf("Ingrese el elemento b[2]\n");
	scanf("%d", &(b->y));
	printf("Ingrese el elemento b[3]\n");
	scanf("%d", &(b->z));
	pv=(struct vector *)malloc(sizeof(struct vector));
	pvec(a,b,pv);
	printf("El producto vectorial es:\n");
	printf("%d\n", pv->x);
	printf("%d\n", pv->y);
	printf("%d\n", pv->z);
	free(a);
	free(b);
	free(pv);
	return 0;
}

int pvec(struct vector *a,struct vector *b,struct vector *pv){
	pv->x=(*a).y*(*b).z-(*a).z*(*b).y;
	pv->y=(*a).z*(*b).x-(*a).x*(*b).z;
	pv->z=(*a).x*(*b).y-(*a).y*(*b).x;
	return pv;
}
