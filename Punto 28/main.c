/*
 * main.c
 *
 *  Created on: 15/10/2013
 *      Author: usuario
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
   char c,*l;
   l=&c;
   int i=0,j=0,n=0,A[10][10];
   int inicioX,inicioY,finX,finY;
   FILE *fp;
   fp = fopen("texto","r");
   while((c=fgetc(fp))!=EOF){
	   /*Para saber en qué parte del texto estamos*/
	   if((c)=='#'){
		   while(fgetc(fp)!='\n'){;}
		   n++;
	   }
	   /*Empieza la primera parte del texto*/
	   else if((n>=1)&&(n<=10)){
		   if(c=='\n'){n++;}
		   else{
			   if(j>9){i++;j=0;}
			   A[i][j]=atoi(l);
			   j++;
		   }
	   }
	   /*Empieza la segunda parte del texto*/
	   else if((n>11)){
		   fscanf(fp,"nicio=(%d,%d)\nfin=(%d,%d)", &inicioX,&inicioY,&finX,&finY);
		   break;
	   }
   }
   printf("La matriz es:\n");
   for(i=0;i<10;i++){
	   for(j=0;j<10;j++){
		   printf("%d",A[i][j]);
	   }
	   printf("\n");
   }
   printf("\nLas coordenadas iniciales y finales son:\n");
   printf("InicioX:%d  InicioY:%d\nFinX:%d  FinY:%d\n",inicioX,inicioY,finX,finY);
   fclose(fp);
   return 0;
}
