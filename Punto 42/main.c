/*
 * main.c
 *
 *  Created on: Nov 11, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/signum.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

#define ID_SEMAFORO "/semaforo_prueba"
#define ENTRADA_PIPE 0
#define SALIDA_PIPE 1

float **a, **b, **c;
int m,n,p;
struct son_dataI{ //estructura que almacena información para los hijos
	int id;
	int n;
	int p;
};
sem_t* semaforo;
float **alloc(int fila, int col);
void printM(float **mat, int fil, int col, int num);
void calcfila(void *arg, int extremo_tuberia);
void mmult(int id, int n, int p);

int main(){
	int i,j,m,n,p;
	printf("Ingrese la cantidad de filas de A\n");
	scanf("%d",&m);
	printf("Ingrese la cantidad de columnas de A (y filas de B)\n");
	scanf("%d",&n);
	printf("Ingrese la cantidad de columnas de B\n");
	scanf("%d",&p);
	a=alloc(m,n);
	b=alloc(n,p);
	c=alloc(m,p);
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
	printM(a,m,n,1);
	printM(b,n,p,2);
	struct son_dataI *input;
	input=(struct son_dataI *)malloc(sizeof(struct son_dataI));
	input->n=n;
	input->p=p;
	for(i=0;i<m;i++){
		for(j=0;j<p;j++){
			c[i][j]=0;
		}
	}
	pid_t hijo[m];
	int tuberia[2];
	pipe(tuberia);
	int id=0; //id para distinguir padre/hijo. También le asigna identificación al hijo para saber qué fila trabajará.
	for(i=0;i<m;i++){
		hijo[i]=fork();
		if(hijo[i]== -1){
			perror("Error al crear proceso hijo");
			exit(1);
		}
		else if(hijo[i]==0){
			/*Cosas del hijo*/
			close(tuberia[ENTRADA_PIPE]);
			id=i+1;
			input->id=id;
			calcfila((void *)input,tuberia[SALIDA_PIPE]);
			exit(0);
		}
	}
	/*Cosas del padre*/
	float v[p+1];
	int status;
	close(tuberia[SALIDA_PIPE]);
	semaforo=sem_open(ID_SEMAFORO,O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	for(i=0;i<m;i++){
		waitpid(hijo[i],&status,0);
		read(tuberia[ENTRADA_PIPE],v, sizeof(v));
		id=v[0];
		for(j=1;j<p+1;j++){
			c[id][j-1]=*(v+j);
		}
	}
	sem_close(semaforo);
	sem_unlink(ID_SEMAFORO);
	printM(c,m,p,3);
	for(i=0;i<m;i++){
		free(a[i]);
	}
	free(a);
	for(i=0;i<n;i++){
		free(b[i]);
	}
	free(b);

	for(i=0;i<m;i++){
		free(c[i]);
	}
	free(c);
	return 0;
}

float **alloc(int fila, int col){ //funcion para generar matrices
	int i;
	float *vals, **temp;
	vals=(float *)malloc(fila*col*sizeof(float));
	temp=(float **)malloc(fila*sizeof(float*));
	for(i=0;i<fila;i++){
		temp[i]=&(vals[i*col]);
	}
	return temp;
}

void printM(float **mat, int fil, int col, int num){ //Para imprimir matrices
	int i,j;
	if(num==1){
		printf("La matriz A(%dx%d) es:\n",fil,col);
	}
	else if(num==2){
		printf("La matriz B(%dx%d) es:\n",fil,col);
	}
	else if(num==3){
		printf("La matriz C(%dx%d) es:\n",fil,col);
	}
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
}

void calcfila(void *arg,int extremo_tuberia){ //Función principal de los hijos
	struct son_dataI *data;
	data = (struct son_dataI *) arg;
	int id = (data->id)-1;
	int n = data->n;
	int p = data->p;
	int i;
	float vfila[p+1];
	semaforo=sem_open(ID_SEMAFORO,O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	mmult(id,n,p);
	vfila[0]=id;
	for(i=1;i<p+1;i++){
		vfila[i]=c[id][i-1];
	}
	sem_wait(semaforo);
	write(extremo_tuberia,vfila,sizeof(vfila));
	sem_post(semaforo);
	usleep(50000);
}

void mmult(int id, int n, int p){ //Sólo álgebra
	int j,k;
	for(j=0;j<p;j++){
		for(k=0;k<n;k++){
			c[id][j] = c[id][j] + a[id][k] * b[k][j];
		}
	}
}
