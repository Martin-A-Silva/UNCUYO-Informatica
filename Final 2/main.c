/*
 * main.c
 *
 *  Created on: 19/11/2013
 *      Author: usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listas.h"
#include <string.h>


int main(){
	inicio();
	int i,n;
	printf("¿Cuántos nodos desea usted que tenga la lista?\n");
	scanf("%d",&n);
	if(n<1){
		printf("ERROR! La lista no puede tener menos de 1 nodo!");
		exit(1);
	}
	printf("\nSus deseos son instrucciones de máquina...\n");
	for(i=1;i<n;i++){
		agregar();
	}
	mostrar();
	char *string;
	string=(char *)malloc(sizeof(char));
	int respuesta;
	while(strcmp(string,"salir")!=0){
		printf("Escriba si quiere agregar, eliminar o modificar algún elemento de la lista, o si desea salir.\n");
		scanf("%s",string);
		respuesta=strcmp(string,"agregar");
		if(respuesta==0){
			printf("¿Cuántos nodos desea usted agregar a la lista?\n");
			scanf("%d",&n);
			if(n<1){
				printf("ERROR! Debe agregar al menos 1 nodo!");
				exit(1);
			}
			for(i=0;i<n;i++){
				agregar();
				mostrar();
			}
		}
		respuesta=strcmp(string,"eliminar");
		if(respuesta==0){
			eliminar();
			mostrar();
		}
		respuesta=strcmp(string,"modificar");
		if(respuesta==0){
			modificar();
			mostrar();
		}
	}
	printf("Adiós, mundo cruel...\n");
	return 0;
}
