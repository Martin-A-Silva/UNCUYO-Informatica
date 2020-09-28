/*
 * main.c
 *
 *  Created on: Oct 21, 2013
 *      Author: martin
 */

#include<stdio.h>
#include<math.h>

int main(){
	float v1[3],a,b,c,va[4],vb[4],vc[4];
	int i;
	va[3]=1,vb[3]=1,vc[3]=1;
	printf("Ingrese los valores \"x\", \"y\", y \"z\"\n");
	for(i=0;i<3;i++){
		scanf("%f",&v1[i]);
	}
	printf("Ingrese los ángulos de rotación alrededor de \"x0\", \"y0\", y de \"z0\"\n");
	scanf("%f",&a);
	scanf("%f",&b);
	scanf("%f",&c);
	//Para la rotación en x
	for(i=0;i<3;i++){
		if(i==1){
			va[i]=cos(a)*v1[i]+sin(a)*v1[2];
		}
		else if(i==2){
			va[i]=cos(a)*v1[i]-sin(a)*v1[1];
		}
		else{
			va[i]=v1[1];
		}
	}
	//Para la rotación en y
	for(i=0;i<3;i++){
		if(i==0){
			vb[i]=cos(b)*v1[i]+sin(b)*v1[2];
		}
		else if(i==2){
			vb[i]=cos(b)*v1[i]-sin(b)*v1[0];
		}
		else{
			vb[i]=v1[1];
		}
	}
	//Para la rotación en z
	for(i=0;i<3;i++){
		if(i==0){
			vc[i]=cos(c)*v1[i]+sin(c)*v1[1];
		}
		else if(i==1){
			vc[i]=cos(c)*v1[i]-sin(c)*v1[0];
		}
		else{
			vc[i]=v1[1];
		}
	}
	printf("El vector de rotación alrededor de \"x\" es:\n");
	for(i=0;i<4;i++){
		printf("%f\n",va[i]);
	}
	printf("El vector de rotación alrededor de \"y\" es:\n");
	for(i=0;i<4;i++){
		printf("%f\n",vb[i]);
	}
	printf("El vector de rotación alrededor de \"z\" es:\n");
	for(i=0;i<4;i++){
		printf("%f\n",vc[i]);
	}
	printf("Dato curioso: La nota del ejercicio 35 es falsa ");
	return 0;
}
