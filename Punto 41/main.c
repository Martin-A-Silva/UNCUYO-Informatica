/*
 * main.c
 *
 *  Created on: Oct 28, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float **a, **b, **c;

struct thread_data{ //se define una estructura para pasar más de un dato a un thread
	int t;
	int m;
	int n;
	int p;
};

float **alloc(int fila, int col) { //generación dinámica de las matrices
	int i;
	float *vals, **temp;

	vals = (float *) malloc (fila * col * sizeof(float));

	temp = (float **) malloc (fila * sizeof(float*));

	for(i=0; i < fila; i++){
		temp[i] = &(vals[i * col]);
	}
	return temp;
}

void printMatrix(float **mat, int fila, int col, int num) { //función para imprimir por pantalla las matrices. "num" sirve para saber cual matriz se recibe.
	int i,j;
	if(num==1){
		printf("La matriz A(%dx%d) es:\n", fila, col);
	}
	else if(num==2){
		printf("La matriz B(%dx%d) es:\n", fila, col);
	}
	else if(num==3){
		printf("La matriz C(%dx%d) es:\n", fila, col);
	}
	for(i=0; i < fila; i++){
		for(j=0; j < col; j++)
			printf("%f ",  mat[i][j]);
		printf("\n");
	}
}

void mmult(int id, int m, int n, int p) { //funcion que usarán los threads para calcular la fila.
	int i,j,k;
	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			c[id][j] = 0.0;
			for (k = 0; k < n; k++) {
				c[id][j] = c[id][j] + a[id][k] * b[k][j];
			}
		}
	}
}

void *worker(void *arg){ //función inicial del thread donde se "descomprimen" los argumentos y luego se multiplica.
	struct thread_data *tdata;
	tdata= (struct thread_data *) arg;
	int id = tdata->t;
	int m =tdata->m;
	int n =tdata->n;
	int p =tdata->p;
	mmult(id,m,n,p);
	return 0;
}


int main() {

	int i,j,m,n,p;
	pthread_t *threads;
	printf("Ingrese la cantidad de filas de la matriz A\n");
	scanf("%d",&m);
	printf("Ingrese la cantidad de columnas de A y filas de B\n");
	scanf("%d",&n);
	printf("Ingrese la cantidad de columnas de B\n");
	scanf("%d",&p);

	struct thread_data th_data_arr[m]; //creamos un arreglo que contendrá datos para threads

	a = alloc(m,n); //generación de matrices
	b = alloc(n,p);
	c = alloc(m,p);

	printf("Inicialización de la matriz A(%dx%d)\n",m,n);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			printf("Ingrese el valor del elemento %d%d \n", (i+1),(j+1));
			scanf("%f", &a[i][j]);
		}
	printf("Inicialización de la matriz B(%dx%d)\n",n,p);
	for (i = 0; i < n; i++)
		for (j = 0; j < p; j++) {
			printf("Ingrese el valor del elemento %d%d \n", (i+1),(j+1));
			scanf("%f", &b[i][j]);
		}

    printMatrix(a,m,n,1);
    printMatrix(b,n,p,2);

    threads = (pthread_t *) malloc(m * sizeof(pthread_t));

    for (i = 0; i < m; i++) {
    	th_data_arr[i].t=i;
    	th_data_arr[i].m=m;
    	th_data_arr[i].n=n;
    	th_data_arr[i].p=p;
    	pthread_create(&threads[i], NULL, worker, (void *)&th_data_arr[i]);
    }

    for (i = 0; i < m; i++) {
    	pthread_join(threads[i], NULL);
    }
    printMatrix(c,m,p,3);
    return 0;
}
