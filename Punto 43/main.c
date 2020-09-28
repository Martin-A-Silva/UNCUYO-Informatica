#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 	//Funciones sleep
#include <pthread.h>	//Threads
#include "hidapi.h"		//USB-HID
typedef int boolean;
#define TRUE 1
#define FALSE 0
boolean en_ejecucion;

void *captura_finalizacion(void *arg){
	getchar(); //Este extrae del buffer del teclado el ENTER que quedo de la seleccion del usuario
	getchar(); //Este captura realmente el nuevo ENTER que el usuario presiona para terminar la ejecucion
	en_ejecucion=FALSE;
	return NULL;
}


//Muestra el contenido del buffer de manera "raw" (cruda). Muestra los valores leidos del dispositivo, byte por byte, en sistema decimal
void despliega_salida_cruda(unsigned char buffer[], int LONGITUD_BUFFER){
	int i;
	for(i = 0; i < LONGITUD_BUFFER; i++){
		//Relleno para que todos los numeros muestren 3 cifras
		if(buffer[i] < 100)
			printf("0");
		if(buffer[i] < 10)
			printf("0");

		//Mostramos el valor leido
		printf("%d ", buffer[i]);
	}
	printf("\n");
}

int min_x=0, min_y=0, max_x=100, max_y=100,posX=50,posY=50;


//Muestra el contenido del buffer de manera procesada, agregando semantica a cada grupo de bytes/bits
void despliega_salida_mouse_usb(unsigned char buffer[]){

	//Esto está pensado para un mouse gamer Dragunov (Fabricante: Dragon War)
	printf("Botón izquierdo: %s\n", buffer[0]==1||buffer[0]==3||buffer[0]==5||buffer[0]==7||buffer[0]==9||buffer[0]==11||buffer[0]==13||buffer[0]==15||buffer[0]==17||buffer[0]==21||buffer[0]==23||buffer[0]==25||buffer[0]==27||buffer[0]==29||buffer[0]==31?"PRESIONADO":"LIBRE");
	printf("Botón derecho: %s\n", buffer[0]==2||buffer[0]==3||buffer[0]==6||buffer[0]==7||buffer[0]==10||buffer[0]==11||buffer[0]==14||buffer[0]==15||buffer[0]==19||buffer[0]==22||buffer[0]==23||buffer[0]==26||buffer[0]==30||buffer[0]==31?"PRESIONADO":"LIBRE");
	printf("Botón de pulgar adelante: %s\n",buffer[0]==16||buffer[0]==17||buffer[0]==18||buffer[0]==19||buffer[0]==20||buffer[0]==21||buffer[0]==22||buffer[0]==23||buffer[0]==24||buffer[0]==25||buffer[0]==26||buffer[0]==27||buffer[0]==28||buffer[0]==29||buffer[0]==30||buffer[0]==31?"PRESIONADO":"LIBRE");
	printf("Botón de pulgar atrás: %s\n",buffer[0]==8||buffer[0]==9||buffer[0]==10||buffer[0]==11||buffer[0]==12||buffer[0]==13||buffer[0]==14||buffer[0]==15||buffer[0]==24||buffer[0]==25||buffer[0]==26||buffer[0]==27||buffer[0]==28||buffer[0]==29||buffer[0]==30||buffer[0]==31?"PRESIONADO":"LIBRE");
	printf("Botón scroll (rueda): %s\n", buffer[0] == 4 ||buffer[0]==5||buffer[0]==6||buffer[0]==7||buffer[0]==12||buffer[0]==13||buffer[0]==14||buffer[0]==15||buffer[0]==20||buffer[0]==21||buffer[0]==22||buffer[0]==23||buffer[0]==28||buffer[0]==29||buffer[0]==30||buffer[0]==31?"PRESIONADO":"LIBRE");
	printf("Scroll arriba/abajo: %s\n", buffer[4] == 1?"ARRIBA": buffer[4] ==255?"ABAJO":"LIBRE");
	printf("Posicion X: %d\n", buffer[1]>220 && buffer[2]==15 && posX>min_x? posX=posX-1:((1<buffer[1])&&(buffer[1]<25)) && buffer[2]==0 && posX<max_x? posX=posX+1: posX);
	printf("Posicion Y: %d\n", buffer[2]>1 && buffer[3]==0 && posY>min_y? posY=posY-1:buffer[2]>1 && buffer[3]==255 && posY<max_y? posY=posY+1: posY);
}

int main(){
	struct hid_device_info *dispositivos_disponibles, *dispositivo_actual;

	//Listamos los dispositivos USB-HID conectados (los argumentos en 0 indican que se listen todos, sin filtro por vendor_id o product_id)
	dispositivos_disponibles = hid_enumerate(0x0, 0x0);
	dispositivo_actual = dispositivos_disponibles;
	printf("\nDispositivos encontrados:\n========================\n");
	int i=1;

	while(dispositivo_actual) {
		printf("%d. Vendor Id   : %04hx\n", i, dispositivo_actual->vendor_id);
		printf("   Product Id  : %04hx\n", dispositivo_actual->product_id);
		printf("   Path        : %s\n",  dispositivo_actual->path);
		printf("   No. de serie: %ls\n", dispositivo_actual->serial_number);
		printf("   Fabricante  : %ls\n", dispositivo_actual->manufacturer_string);
		printf("   Producto    : %ls\n", dispositivo_actual->product_string);
		printf("   Release     : %hx\n", dispositivo_actual->release_number);
		printf("   Interfaz    : %d\n",  dispositivo_actual->interface_number);
		printf("\n");
		dispositivo_actual = dispositivo_actual->next;
		i++;
	}

	//Permitimos al usuario seleccionar el dispositivo a muestrear
	int cantidad_dispositivos = i-1;
	int opcion;
	printf("Elija el dispositivo a monitorear (0 = SALIR): ");
	scanf("%d", &opcion);
	while(opcion < 0 || opcion > cantidad_dispositivos){
		printf("Opción invalida! Elija una opción entre 0 y %d", cantidad_dispositivos);
		scanf("%d", &opcion);
	}

	if(opcion != 0){
		//Buscamos el dispositivo elegido por el usuario
		dispositivo_actual = dispositivos_disponibles;
		for(i = 1; i < opcion; i++){
			if(dispositivo_actual->next)
				dispositivo_actual = dispositivo_actual->next;
		}

		//Abrimos el dispositivo
		hid_device *dispositivo;
		dispositivo = hid_open(dispositivo_actual->vendor_id, dispositivo_actual->product_id, NULL);

		//Lanzamos un thread para capturar la senal de finalizacion (cuando el usuario presiona ENTER)
		pthread_t tid;
		pthread_create(&tid, NULL, captura_finalizacion, NULL);

		//Creamos el buffer
		const int LONGITUD_BUFFER = 5;
		unsigned char buffer[LONGITUD_BUFFER];

		//Leemos la entrada cada 100 ms
		en_ejecucion = TRUE;
		while(en_ejecucion == TRUE){
			//Limpiamos la pantalla (esto no es estandar, depende de cada SO)
			printf("\033[2J");

			//Esperamos 100 ms
			usleep(10000);

			//Leemos del dispositivo
			memset(buffer, 0, sizeof(buffer)); //limpiamos el buffer
			hid_read(dispositivo, buffer, sizeof(buffer));

			//Mostramos por pantalla
			despliega_salida_cruda(buffer, LONGITUD_BUFFER);
			despliega_salida_mouse_usb(buffer);
		}

		pthread_join(tid, NULL);

		//Al salir, cerramos el dispositivo
		hid_close(dispositivo);
	}

	//Liberamos la memoria utilizada por la lista de dispositivos disponibles
	hid_free_enumeration(dispositivos_disponibles);

	//Liberamos otras estructuras de datos internas de la biblioteca hidapi
	hid_exit();

	printf("\n\nEjecución finalizada\n");
	return 0;
}
