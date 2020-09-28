/*
 * main.c
 *
 *  Created on: 19/11/2013
 *      Author: usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
	int temp1,temp2;
	temp1=*a;
	temp2=*b;
	*a=temp2;
	*b=temp1;
}

void quicksort(int *v,int lim_izq,int lim_der){
	int i=lim_izq,j=lim_der-1;
	int pivote=v[lim_der]; //Como pivote usamos siempre el valor de la derecha de la partición
	while(i<=j){
		while((v[i]<pivote)&&(i<lim_der)){ //Buscamos de izquierda a derecha un valor mayor que el pivote
			i++;
		}
		while((v[j]>pivote)&&(j>lim_izq)){ //Buscamos de derecha a izquierda un valor menor que el pivote
			j--;
		}
		if(i<=j){
			swap(&v[i],&v[j]); //Intercambios los valores
			if((i==j)&&(v[i]>pivote)){
				swap(&v[i],&v[lim_der]); // Si "i" y "j" están en el mismo lugar, intercambiamos el valor con el pivote si éste es menor.
			}
			i++;
			j--;
		}
	}
	if(lim_izq<j){
		quicksort(v,lim_izq,j);
	}
	if(lim_der>i){
		quicksort(v,i,lim_der);
	}
}

int main(){
	srand(time(NULL));
	int n=1000,v[n];
	int i;
	for(i=0;i<n;i++){
		v[i]=rand()%(n+1);
	}
	v[rand()%(n+1)]=500;
	int metodo;
	printf("Presione 0 para usar bubblesort o 1 para usar quicksort\n");
	scanf("%d",&metodo);
	int subs=1;
	//Ordenamiento por bubblesort de menor a mayor
	if(metodo==0){
		int temp;
		while(subs==1){
			subs=0;
			for(i=0;i<999;i++){
				if(v[i]>v[i+1]){
					temp=v[i];
					v[i]=v[i+1];
					v[i+1]=temp;
					subs=1;
				}
			}
		}
	}
	//Ordenamiento por quicksort de menor a mayor
	else if(metodo==1){
		int izq=0, der=n-1;
		quicksort(v,izq,der);
	}
	//Búsqueda binaria del valor 500
	subs=1;
	int a=0,b=500,c=1000;
	while(subs==1){
		if(v[a]<500 && 500<v[b]){
			c=b;
			b=(a+b)/2;
		}
		else if(v[b]<500 && 500<v[c]){
			a=b;
			b=(b+c)/2;
		}
		else{
			subs=0;
			printf("El valor %d se encuentra en la posición %d", v[b],b);
		}
	}
	return 0;
}
