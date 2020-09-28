/*
 * main.c
 *
 *  Created on: Oct 5, 2013
 *      Author: martin
 */

#include <stdio.h>

int fibonacci(int n){
	int fibonacci=1,fibonaccia=0,fibonaccib;
	int i;
	if(n==0){
		fibonacci=0;
	}
	else if(n==1){
		fibonacci=1;
	}
	else{
		for(i=2;i<=n;i++){
			fibonaccib=fibonacci;
			fibonacci=fibonacci+fibonaccia;
			fibonaccia=fibonaccib;
		}
	}
	return fibonacci;
}
int main(){
	int a;
	printf ("Por favor, indique qué termino de la sucesión de fibonacci desea conocer \n");
	scanf ("%d", &a);
	printf ("El término f%d es:", a);
	a=fibonacci(a);
	printf("%d \n Gracias por utilizar este programa.", a);
	return 0;
}
