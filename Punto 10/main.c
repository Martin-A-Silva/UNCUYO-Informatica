/*
 * main.c
 *
 *  Created on: Oct 3, 2013
 *      Author: martin
 */

#include<stdio.h>

int main(){
	int i,j;
	float k;
	i=0;j=0;k=0;
	for(i=0;i!=100;i++){
		for(j=0;j!=100;j++){
			if((i-j)!=0){
				k=k+((i+j)/(i-j));
			}
		}
	}
	printf("El resultado de la función es:%f", k);
	return 0;
}
