#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 	//Funciones sleep
#include <pthread.h>	//Threads
#include "hidapi.h"		//USB-HID
#include <sys/socket.h>		//Sockets
#include <arpa/inet.h>		//Sockets
#include <signal.h> 		//Biblioteca para enviar senales a los procesos (kill)
#include <bits/signum.h> 	//Biblioteca conconstantes para los tipos de senales
#include <sys/wait.h>

typedef int boolean;
#define TRUE 1
#define FALSE 0
boolean en_ejecucion;
struct hid_device_info *dispositivos_disponibles, *dispositivo_actual;
#define PUERTO_SERVER 3333
#define MAX_LARGO_COLA 100
#define SERVER 0
#define CLIENTE 1

int rolProceso;
int opcion;
hid_device *dispositivo;

//Esta funcion maneja las señales que recibe del kernel ("interrupciones de software")
 void manejador_signals(int signal_type)
 {
   char rolProceso[10];
   if(rolProceso == SERVER)
 	  strcpy(rolProceso, "Servidor");
   else
 	  strcpy(rolProceso, "Cliente");

   if (signal_type == SIGTERM){
 	  en_ejecucion = FALSE;
 	  printf("%s: Señal SIGTERM recibida. Terminando proceso.\n", rolProceso);
   }
   else if (signal_type == SIGKILL){
 	  en_ejecucion = FALSE;
 	  printf("%s: Señal SIGKILL recibida. Terminando proceso.\n", rolProceso);
   }
   else
 	printf("Señal desconocida. Ignorando...\n\n");
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

 //Funcion que ejecuta el proceso servidor
 void servidor(){
 	int sd; //socket descriptor

 	rolProceso = SERVER;

 	//Creamos el socket:
 	//	AF_INET: Familia de protocolos TCP/IP
 	//	SOCK_STREAM: Servicio orientado a la conexion (normalmente protocolo TCP)
 	sd = socket(AF_INET, SOCK_STREAM, 0);
 	if(sd < 0){
 		 perror("Error al crear socket (servidor)");
 		 abort();
 	}

 	//Creamos la configuracion de direccion para el socket
 	struct sockaddr_in direccionSocket; 						//Estructura para configurar el socket
 	memset(&direccionSocket, 0, sizeof(direccionSocket)); 		//Utilizamos memset para inicializar a 0 todos los bytes de la estructura de configuracion del socket
 	direccionSocket.sin_family = AF_INET; 						//Familia de direcciones de TCP/IP
 	inet_aton("127.0.0.1", &(direccionSocket.sin_addr));		//Especificamos la direccion IP al que se conectara el socket, y la convertimos al formato de la red
 	direccionSocket.sin_port = htons(PUERTO_SERVER);       		//Especificamos el puerto TCP al que se conectara el socket, y lo convertimos al byte order de la red

 	//Enlazamos el socket con la direccion local
 	if(bind(sd, (struct sockaddr *)&direccionSocket,sizeof(direccionSocket)) < 0){
 		perror("Error al enlazar socket al puerto (servidor)");
 		abort();
 	}

 	//Configuramos el socket para que escuche conexiones, y configuramos una cantidad maxima MAX_LARGO_COLA de conexiones que podemos poner en la cola
 	listen(sd, MAX_LARGO_COLA);

 	//Creamos las variables requeridas para esperar una conexion
 	struct sockaddr_in direccionSocketCliente;
 	socklen_t longitudDireccionCliente;
 	int sd_aceptado;  //socket creado automaticamente cuando se acepta una conexion

 	//El proceso se bloquea esperando una conexion
 	sd_aceptado = accept(sd, (struct sockaddr *)&direccionSocketCliente, &longitudDireccionCliente);

 	//Creamos el buffer
 	const int LONGITUD_BUFFER = 5;
 	unsigned char buffer_lectura[LONGITUD_BUFFER];

 	while(en_ejecucion){

 		memset(buffer_lectura, 0, sizeof(buffer_lectura)); //limpiamos el buffer
 		recv(sd_aceptado, buffer_lectura, sizeof(buffer_lectura), 0);
 		//Mostramos lo recibido por pantalla

 			printf("\033[2J");
 			usleep(10000);
 			//Mostramos lo recibido por pantalla
 			despliega_salida_cruda(buffer_lectura, LONGITUD_BUFFER);
 			despliega_salida_mouse_usb(buffer_lectura);

 	}

 	//Cerramos el nuevo socket creado con accept
 	close(sd_aceptado);

 	//Cerramos el socket original
 	close(sd);
 }

 //Funcion que ejecuta el proceso cliente
 void cliente(){
 	int sd; //socket descriptor

 	rolProceso = CLIENTE;

 	//Creamos el socket:
 	//	AF_INET: Familia de protocolos TCP/IP
 	//	SOCK_STREAM: Servicio orientado a la conexion (normalmente protocolo TCP)
 	sd = socket(AF_INET, SOCK_STREAM, 0);
 	if(sd < 0){
 		perror("Error al crear socket (cliente)");
 		abort();
 	}

 	//Creamos la configuracion de direccion para el socket
 	struct sockaddr_in direccionSocket; 						//Estructura para configurar el socket
 	memset(&direccionSocket, 0, sizeof(direccionSocket)); 		//Utilizamos memset para inicializar a 0 todos los bytes de la estructura de configuracion del socket
 	direccionSocket.sin_family = AF_INET; 						//Familia de direcciones de TCP/IP
 	inet_aton("127.0.0.1", &(direccionSocket.sin_addr));		//Especificamos la direccion IP al que se conectara el socket, y la convertimos al formato de la red
 	direccionSocket.sin_port = htons(PUERTO_SERVER);       		//Especificamos el puerto TCP al que se conectara el socket, y lo convertimos al byte order de la red

 	//Establecemos conexion con el server
 	int conectado;
 	dispositivo_actual = dispositivos_disponibles;
 	//Buscamos el dispositivo elegido por el usuario
 	int i;
 	for(i = 1; i < opcion; i++){
 		if(dispositivo_actual->next)
 			dispositivo_actual = dispositivo_actual->next;
 	}

 	//Abrimos el dispositivo
 	hid_device *dispositivo;
 	dispositivo = hid_open(dispositivo_actual->vendor_id, dispositivo_actual->product_id, NULL);

 	do{
 		sleep(1);
 		conectado = connect(sd, (struct sockaddr *)&direccionSocket,sizeof(direccionSocket));
 	}while(conectado < 0);
 	//Creamos el buffer
 	const int LONGITUD_BUFFER = 5;
 	unsigned char buffer_envio[LONGITUD_BUFFER];

 	while(en_ejecucion){
 		usleep(10000);

 		//Leemos del dispositivo
 		memset(buffer_envio, 0, sizeof(buffer_envio)); //limpiamos el buffer
 		hid_read(dispositivo, buffer_envio, sizeof(buffer_envio));

 		//Enviamos mensaje al servidor
 		send(sd, buffer_envio, sizeof(buffer_envio), 0);

 	}

 	close(sd);
 }

 int main(){

 	//Listar los dispositivos USB-HID conectados
 	dispositivos_disponibles = hid_enumerate(0x0, 0x0);
 	dispositivo_actual = dispositivos_disponibles;
 	printf("\nDispositivos USB conectados:""\n===========================\n");
 	int i=1;

 	//Bucle que busca y muestra uno por uno los dispositivos
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

 	//Seleccionar el dispositivo a muestrear
 	int cantidad_dispositivos = i-1;
 	//int opcion;
 	printf("Elija el dispositivo a monitorear (0 = SALIR): ");
 	scanf("%d", &opcion);
 	while(opcion < 0 || opcion > cantidad_dispositivos){
 		printf("Opción invalida! Elija una opción entre 0 y %d", cantidad_dispositivos);
 		scanf("%d", &opcion);
 	}
 	if(opcion != 0){

 		en_ejecucion = TRUE;

 		//ID de los procesos
 		pid_t pid_servidor;
 		pid_t pid_cliente;

 		//Registramos con el kernel la funcion que maneja las signals
 		signal(SIGINT, manejador_signals);
 		signal(SIGTERM, manejador_signals);

 		pid_servidor = fork();
 		if(pid_servidor == -1){
 			printf("Error al iniciar servidor");
 		}
 		else if(pid_servidor == 0){
 			servidor();
 			exit(0);
 		}else{
 			pid_cliente = fork();
 			if(pid_cliente == -1){
 				printf("Error al iniciar el cliente");
 			}
 			else if(pid_cliente == 0){
 				cliente(dispositivo);
 				exit(0);
 			}
 			else{
 				getchar();//captura la elección del programa (lo que en el ejercicio 43 se hace en la función captura_finalización
 				getchar();
 				getchar();

 				kill(pid_servidor, SIGTERM);
 				kill(pid_cliente, SIGTERM);

 				int status;
 				waitpid(pid_servidor, &status, 0);
 				waitpid(pid_cliente, &status, 0);

 				printf("\n\nEjecución finalizada.\n");
 			}
 		}

 		//Al salir, cerramos el dispositivo
 		hid_close(dispositivo);
 		//Liberamos la memoria utilizada por la lista de dispositivos disponibles
 		hid_free_enumeration(dispositivos_disponibles);
 		//Liberamos otras estructuras de datos internas de la biblioteca hidapi
 		hid_exit();

 	}//cierra el if de la parte de USB
 	return 0;
 }
