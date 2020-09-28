/*
 * main.c
 *
 *  Created on: Oct 23, 2013
 *      Author: martin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		   printf("%d",A[i][j]);
	   }
	   printf("\n");
   }
   printf("\nLas coordenadas iniciales y finales son:\n");
   printf("InicioX:%d  InicioY:%d\nFinX:%d  FinY:%d\n",inicioX,inicioY,finX,finY);
   for(i=0;i<row;i++){
	   free(A[i]);
   }
   free(A);
   fclose(fp);
   return 0;
}
