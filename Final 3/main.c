/*
 * main.c
 *
 *  Created on: Nov 21, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 2
#define DONTKNOW 1
#define FALSE 0
#define LEIDO 1
#define NOLEIDO 0

int leidos[8]={0,0,0,0,0,0,0,0}; //Cada elemento indica si ya hemos intentado leer un nodo limítrofe.
int solucion=DONTKNOW;

typedef struct NODO_SUCESOR{
	int fil;
	int col;
	int valor;
	struct NODO_SUCESOR *UL;
	struct NODO_SUCESOR *UU;
	struct NODO_SUCESOR *UR;
	struct NODO_SUCESOR *LL;
	struct NODO_SUCESOR *RR;
	struct NODO_SUCESOR *DL;
	struct NODO_SUCESOR *DD;
	struct NODO_SUCESOR *DR;
	struct NODO_SUCESOR *anterior;
}NODO;
NODO *raiz;
NODO *sucesor_actual;
typedef struct CAMINO_RECORRIDO{
	int fil;
	int col;
	struct CAMINO_RECORRIDO *anterior;
	struct CAMINO_RECORRIDO *siguiente;
}CAMINO;
CAMINO *camino;

void inicio(int **A, int inicioX, int inicioY){
	raiz =(NODO *)malloc(sizeof(NODO));
   	raiz->fil=inicioX;
   	raiz->col=inicioY;
   	raiz->valor=A[inicioX][inicioY];
   	raiz->anterior=NULL;
}

   /* Creamos un nodo en una dirección, le asignamos su fila y columna,
    * nos cercioramos de que tenga correspondencia con la matriz,
    * le asignamos su valor y su nodo padre, si no ha sido leido
    * y no es un espacio ocupado nos desplazamos, sino lo borramos
    * pero lo marcamos como leído. */

void mover_UL(int ***B,int rows,int cols){
	sucesor_actual->UL=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->UL->fil=sucesor_actual->fil-1;
   	sucesor_actual->UL->col=sucesor_actual->col-1;
   	if((sucesor_actual->UL->fil>=0)&&(sucesor_actual->UL->col>=0)&&(sucesor_actual->UL->fil<rows)&&(sucesor_actual->UL->col<cols)){// Para evitar SEGFAULT
   		sucesor_actual->UL->valor=B[sucesor_actual->UL->fil][sucesor_actual->UL->col][0];//En B[i,j,0] está el valor del mapa (0 ó 1)
   		sucesor_actual->UL->anterior=sucesor_actual;
   		if((B[sucesor_actual->UL->fil][sucesor_actual->UL->col][1]==NOLEIDO)&&(B[sucesor_actual->UL->fil][sucesor_actual->UL->col][0]==0)){
   			sucesor_actual=sucesor_actual->UL;                                        //Si no está leido y es un espacio vacío, nos movemos
   			B[sucesor_actual->fil][sucesor_actual->col][1]=LEIDO;
   		}
   		else{
   			leidos[0]=1;
   			free(sucesor_actual->UL);
   		}
   	}
   	else{
   		leidos[0]=1;
   		free(sucesor_actual->UL);
   	}
   }
void mover_UU(int ***B,int rows,int cols){
   	sucesor_actual->UU=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->UU->fil=sucesor_actual->fil-1;
   	sucesor_actual->UU->col=sucesor_actual->col;
   	if((sucesor_actual->UU->fil>=0)&&(sucesor_actual->UU->col>=0)&&(sucesor_actual->UU->fil<rows)&&(sucesor_actual->UU->col<cols)){
   		sucesor_actual->UU->valor=B[sucesor_actual->UU->fil][sucesor_actual->UU->col][0];
   		sucesor_actual->UU->anterior=sucesor_actual;
   		if((B[sucesor_actual->UU->fil][sucesor_actual->UU->col][1]==NOLEIDO)&&(B[sucesor_actual->UU->fil][sucesor_actual->UU->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->UU;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[1]=1;
   			free(sucesor_actual->UU);
   		}
   	}
   	else{
   		leidos[1]=1;
   		free(sucesor_actual->UU);
   	}
   }
void mover_UR(int ***B,int rows,int cols){
   	sucesor_actual->UR=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->UR->fil=sucesor_actual->fil-1;
   	sucesor_actual->UR->col=sucesor_actual->col+1;
   	if((sucesor_actual->UR->fil>=0)&&(sucesor_actual->UR->col>=0)&&(sucesor_actual->UR->fil<rows)&&(sucesor_actual->UR->col<cols)){
   		sucesor_actual->UR->valor=B[sucesor_actual->UR->fil][sucesor_actual->UR->col][0];
   		sucesor_actual->UR->anterior=sucesor_actual;
   		if((B[sucesor_actual->UR->fil][sucesor_actual->UR->col][1]==NOLEIDO)&&(B[sucesor_actual->UR->fil][sucesor_actual->UR->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->UR;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[2]=1;
   			free(sucesor_actual->UR);
   		}
   	}
   	else{
   		leidos[2]=1;
   		free(sucesor_actual->UR);
   	}
   }
void mover_LL(int ***B,int rows,int cols){
   	sucesor_actual->LL=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->LL->fil=sucesor_actual->fil;
   	sucesor_actual->LL->col=sucesor_actual->col-1;
   	if((sucesor_actual->LL->fil>=0)&&(sucesor_actual->LL->col>=0)&&(sucesor_actual->LL->fil<rows)&&(sucesor_actual->LL->col<cols)){
   		sucesor_actual->LL->valor=B[sucesor_actual->LL->fil][sucesor_actual->LL->col][0];
   		sucesor_actual->LL->anterior=sucesor_actual;
   		if((B[sucesor_actual->LL->fil][sucesor_actual->LL->col][1]==NOLEIDO)&&(B[sucesor_actual->LL->fil][sucesor_actual->LL->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->LL;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[3]=1;
   			free(sucesor_actual->LL);
   		}
   	}
   	else{
   		leidos[3]=1;
   		free(sucesor_actual->LL);
   	}
   }
void mover_RR(int ***B,int rows,int cols){
   	sucesor_actual->RR=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->RR->fil=sucesor_actual->fil;
   	sucesor_actual->RR->col=sucesor_actual->col+1;
   	if((sucesor_actual->RR->fil>=0)&&(sucesor_actual->RR->col>=0)&&(sucesor_actual->RR->fil<rows)&&(sucesor_actual->RR->col<cols)){
   		sucesor_actual->RR->valor=B[sucesor_actual->RR->fil][sucesor_actual->RR->col][0];
   		sucesor_actual->RR->anterior=sucesor_actual;
   		if((B[sucesor_actual->RR->fil][sucesor_actual->RR->col][1]==NOLEIDO)&&(B[sucesor_actual->RR->fil][sucesor_actual->RR->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->RR;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[4]=1;
   			free(sucesor_actual->RR);
   		}
   	}
   	else{
   		leidos[4]=1;
   		free(sucesor_actual->RR);
   	}
   }
void mover_DL(int ***B,int rows,int cols){
   	sucesor_actual->DL=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->DL->fil=sucesor_actual->fil+1;
   	sucesor_actual->DL->col=sucesor_actual->col-1;
   	if((sucesor_actual->DL->fil>=0)&&(sucesor_actual->DL->col>=0)&&(sucesor_actual->DL->fil<rows)&&(sucesor_actual->DL->col<cols)){
   		sucesor_actual->DL->valor=B[sucesor_actual->DL->fil][sucesor_actual->DL->col][0];
   		sucesor_actual->DL->anterior=sucesor_actual;
   		if((B[sucesor_actual->DL->fil][sucesor_actual->DL->col][1]==NOLEIDO)&&(B[sucesor_actual->DL->fil][sucesor_actual->DL->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->DL;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[5]=1;
   			free(sucesor_actual->DL);
   		}
   	}
   	else{
   		leidos[5]=1;
   		free(sucesor_actual->DL);
   	}
   }
void mover_DD(int ***B,int rows,int cols){
   	sucesor_actual->DD=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->DD->fil=sucesor_actual->fil+1;
   	sucesor_actual->DD->col=sucesor_actual->col;
   	if((sucesor_actual->DD->fil>=0)&&(sucesor_actual->DD->col>=0)&&(sucesor_actual->DD->fil<rows)&&(sucesor_actual->DD->col<cols)){
   		sucesor_actual->DD->valor=B[sucesor_actual->DD->fil][sucesor_actual->DD->col][0];
   		sucesor_actual->DD->anterior=sucesor_actual;
   		if((B[sucesor_actual->DD->fil][sucesor_actual->DD->col][1]==NOLEIDO)&&(B[sucesor_actual->DD->fil][sucesor_actual->DD->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->DD;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[6]=1;
   			free(sucesor_actual->DD);
   		}
   	}
   	else{
   		leidos[6]=1;
   		free(sucesor_actual->DD);
   	}
   }
void mover_DR(int ***B,int rows,int cols){
   	sucesor_actual->DR=(NODO *)malloc(sizeof(NODO));
   	sucesor_actual->DR->fil=sucesor_actual->fil+1;
   	sucesor_actual->DR->col=sucesor_actual->col+1;
   	if((sucesor_actual->DR->fil>=0)&&(sucesor_actual->DR->col>=0)&&(sucesor_actual->DR->fil<rows)&&(sucesor_actual->DR->col<cols)){
   		sucesor_actual->DR->valor=B[sucesor_actual->DR->fil][sucesor_actual->DR->col][0];
   		sucesor_actual->DR->anterior=sucesor_actual;
   		if((B[sucesor_actual->DR->fil][sucesor_actual->DR->col][1]==NOLEIDO)&&(B[sucesor_actual->DR->fil][sucesor_actual->DR->col][0]==0)){ //Si no está leido, nos movemos
   			sucesor_actual=sucesor_actual->DR;
   			B[sucesor_actual->fil][sucesor_actual->col][1]=1;
   		}
   		else{
   			leidos[7]=1;
   			free(sucesor_actual->DR);
   		}
   	}
   	else{
   		leidos[7]=1;
   		free(sucesor_actual->DR);
   	}
   }


int main(){
   char c,*l;
   l=&c;
   int a=0,row=-1,col=0,i=0,j=0,n=0,**A;
   int inicioX,inicioY,finX,finY;
   fpos_t pos;
   FILE *fp;
   fp = fopen("texto","r");
   while((c=fgetc(fp))!=EOF){
	   /*Para saber en qué parte del texto estamos*/
	   if((c)=='#'){
		   do{
			   c=fgetc(fp);
		   }while(c!='\n');
		   n++;
	   }
	   if(n==1){
		   fgetpos(fp,&pos);
		   n++;
	   }
	   /*Empieza la lectura de filas y columnas*/
	   if(n==2){
		   if(c=='\n'){
			   if(a==1){
				   n++;
				   col=col/row;
				   A=(int **)calloc(row,sizeof(int *));
				   for(i=0;i<row;i++){
					   A[i]=(int *)calloc(col,sizeof(int));
				   }
				   i=0;
				   fsetpos(fp,&pos);
				   continue;
			   }
			   row++;
			   a++;    //a es una variable auxiliar para ver si hay dos \n seguidos
		   }
		   else{
			   col++;
			   a=0;
		   }
	   }
	   if(n==3){
		   if(c=='\n'){
			   i++;
			   j=0;
		   }
		   else{
			   if(i==row){
				   n++;
				   continue;
			   }
			   A[i][j]=atoi(l);
			   j++;
		   }
	   }
	   /*Empieza la segunda parte del texto*/
	   if((n==4)){
		   fscanf(fp,"inicio=(%d,%d)\nfin=(%d,%d)", &inicioX,&inicioY,&finX,&finY);
		   break;
	   }
   }
   printf("La matriz es:\n");
   for(i=0;i<row;i++){
	   for(j=0;j<col;j++){
		   printf("%d", A[i][j]);
	   }
	   printf("\n");
   }
   printf("\nLas coordenadas iniciales y finales son:\n");
   printf("InicioX:%d  InicioY:%d\nFinX:%d  FinY:%d\n",inicioX,inicioY,finX,finY);
   fclose(fp);
   //----------------------------------------------------------------
   //Final 3
   //----------------------------------------------------------------
   printf("\n");
   srand(time(NULL));
   int ***B;  //Esta matriz es la matriz A, pero con una dimensión más que dice si la celda ha sido leída.
   B=(int ***)calloc(row,sizeof(int **));
   for(i=0;i<row;i++){
	   B[i]=(int **)calloc(col,sizeof(int *));
	   for(j=0;j<col;j++){
		   B[i][j]=(int *)calloc(2,sizeof(int));
	   }
   }
   int chiru;
   int cantleidos=0;
   for(i=0;i<row;i++){
	   for(j=0;j<col;j++){
		   B[i][j][0]=A[i][j];
		   B[i][j][1]=NOLEIDO;
	   }
   }
   inicio(A,inicioX,inicioY);
   sucesor_actual=raiz;
   sucesor_actual->anterior=NULL;
   printf("Que empiece la magia...\n");
   void magic(){
	   chiru=rand()%8;
	   if(chiru==0){
	   		   mover_UL(B,row,col); //Intento moverme arriba a la izquierda.
	   	   }
	   	   else if(chiru==1){
	   		   mover_UU(B,row,col);
	   	   }
	   	   else if(chiru==2){
	   		   mover_UR(B,row,col);
	   	   }
	   	   else if(chiru==3){
	   		   mover_LL(B,row,col);
	   	   }
	   	   else if(chiru==4){
	   		   mover_RR(B,row,col);
	   	   }
	   	   else if(chiru==5){
	   		   mover_DL(B,row,col);
	   	   }
	   	   else if(chiru==6){
	   		   mover_DD(B,row,col);
	   	   }
	   	   else if(chiru==7){
	   		   mover_DR(B,row,col);
	   	   }
	   	   if((sucesor_actual->fil==finX)&&(sucesor_actual->col==finY)){   //Llegamos a la solución
	   		   solucion=TRUE;
	   	   }
	   	   for(i=0;i<8;i++){
	   		   if(leidos[i]==0){ //Si hay algún no leído, seguimos con los movimientos y reiniciamos el conteo de leídos.
	   			   cantleidos=0;
	   			   break;
	   		   }
	   		   cantleidos +=1;
	   		   if(cantleidos==8){ //Si todos los nodos de alrededor están leídos, volvemos al nodo padre.
	   			   for(j=0;j<8;j++){
	   				   leidos[j]=0;
	   			   }
	   			   cantleidos=0;
	   			   if(sucesor_actual->anterior==NULL){ //Si se llega a la raíz, es porque no hay solución.
	   				   solucion=FALSE;
	   			   }
	   			   else{
	   				   sucesor_actual=sucesor_actual->anterior;
	   			   }
	   		   }
	   	   }
	   	   if(solucion==DONTKNOW){
	   		   magic();
	   	   }
   }
   magic();
   if(solucion==TRUE){
	   printf("¡Éxito!\nEl camino recorrido es:\n(Fila)(Columna)\n");
	   camino=(CAMINO *)malloc(sizeof(CAMINO));
	   camino->anterior=NULL;
	   camino->siguiente=NULL;
	   while(sucesor_actual->anterior!=NULL){     //El camino lo fabricamos de atrás para adelante...
		   camino->fil=sucesor_actual->fil;
		   camino->col=sucesor_actual->col;
		   camino->anterior=(CAMINO *)malloc(sizeof(CAMINO));
		   camino->anterior->siguiente=camino;
		   camino=camino->anterior;
		   sucesor_actual=sucesor_actual->anterior;
	   }
	   camino->fil=inicioX;
	   camino->col=inicioY;
	   while(camino->siguiente!=NULL){      //Pero después lo mostramos en orden
		   printf("   %d      %d\n",camino->fil,camino->col);
		   camino=camino->siguiente;
	   }
	   printf("   %d      %d\n",camino->fil,camino->col);
   }
   else if(solucion==FALSE){
	   printf("No hay camino posible\n");
   }
   else{
	   printf("Hubo error...\n");
   }
   for(i=0;i<row;i++){
   	   free(A[i]);
      }
   free(A);
   for(i=0;i<row;i++){
	   for(j=0;j<col;j++){
		   free(B[i][j]);
	   }
	   free(B[i]);
   }
   free(B);
   printf("\nBueno, esto fue el último ejercicio para el Proyecto Final, espero que le haya gustado...chau!\n");
   return 0;
}
