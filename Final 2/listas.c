/*
 * listas.c
 *
 *  Created on: 19/11/2013
 *      Author: usuario
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct NODO_SUCESOR{
	int valor;
	struct NODO_SUCESOR *siguiente;
	struct NODO_SUCESOR *anterior;
}NODO;
NODO *sucesores;
NODO *sucesor_actual;

void inicio(){ //Inicialización

	sucesores =(NODO *)malloc(sizeof(NODO));
	srand(time(NULL));
	sucesores->valor=rand()%30;
	sucesores->anterior=NULL;
	sucesores->siguiente=NULL;

}

void agregar(){

	sucesor_actual=sucesores;
	while(sucesor_actual->siguiente!=NULL){
		sucesor_actual=sucesor_actual->siguiente;
	}
	sucesor_actual->siguiente=(NODO *)malloc(sizeof(NODO));
	sucesor_actual->siguiente->valor=rand()%30;
	sucesor_actual->siguiente->anterior=sucesor_actual;
	sucesor_actual->siguiente->siguiente=NULL;
}

void eliminar(){
	NODO *temp1,*temp2;
	int i,n,tope=0;  //La variable tope se usa para detectar si el nodo a eliminar está fuera de la lista
	sucesor_actual=sucesores;
	printf("¿Qué nodo desea usted eliminar, cruel persona?\n");
	scanf("%d",&n);
	if(n==1){
		sucesor_actual=sucesor_actual->siguiente; //Para cuando se quiere eliminar el primer nodo
		free(sucesor_actual->anterior);
		sucesor_actual->anterior=NULL;
		sucesores=sucesor_actual;
	}
	if(n>1){
		for(i=1;i<n-1;i++){
			sucesor_actual=sucesor_actual->siguiente;
			if(tope==1){
				printf("ERROR! No existe tal nodo.\n");
				exit(1);
			}
			if(sucesor_actual->siguiente==NULL){
				tope=1;
			}
		}
		if(sucesor_actual->siguiente->siguiente==NULL){ //Esto es para cuando se quiere eliminar el último nodo
			free(sucesor_actual->siguiente);
			sucesor_actual->siguiente=NULL;
		}
		else{
			temp1=sucesor_actual->siguiente->siguiente;
			temp2=sucesor_actual;
			free(sucesor_actual->siguiente);
			sucesor_actual->siguiente=temp1;
			sucesor_actual=sucesor_actual->siguiente;
			sucesor_actual->anterior=temp2;
		}
	}
}

void modificar(){
	int n,i,tope=0;
	sucesor_actual=sucesores;
	printf("Ingrese el elemento a modificar: \n");
	scanf("%d", &n);
	if(n<1){
		printf("ERROR! No existe tal nodo.\n");
		exit(1);
	}
	for(i=1;i<n;i++){
		sucesor_actual=sucesor_actual->siguiente;
		if(tope==1){
			printf("ERROR! No existe tal nodo.\n");
			exit(1);
		}
		if(sucesor_actual->siguiente==NULL){
			tope=1;
		}
	}
	printf("El valor actual es: %d\n", sucesor_actual->valor);
	printf("Y lo cambiará por: ");
	scanf ("%d", &sucesor_actual->valor);
	printf("\n");
}

void mostrar(){
	int i=1;
	sucesor_actual=sucesores;
	printf("El elemento número %d es: %d\n",i,sucesor_actual->valor);
	i+=1;
	while(sucesor_actual->siguiente!=NULL){
		sucesor_actual=sucesor_actual->siguiente;
		printf("El elemento número %d es: %d", i,sucesor_actual->valor);
		printf("\n");
		i+=1;
	}
}
