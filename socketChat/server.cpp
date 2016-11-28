#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>   //Libreria que incluye sockaddr_in

#define bffSize 1024

int main(int argc, const char *argv[])
{



	int server, client; //fd -> File Descriptor
	int Nport = 1100;  //El puerto debe ser el mismo en server y client
	bool goOut = false; //Para terminar el bucle
	char buffer[bffSize]; //Donde se escribiran y leeran los mensajes de uno a otro

	struct sockaddr_in server_addr; //contiene la direccion del server
	socklen_t size;

	//1. Creacin del socket

	client = socket(AF_INET, SOCK_STREAM, 0); //AF_INET hace referencia a direccin IP



	if (client < 0)//En caso de que no pueda crearse devolver -1 y se acabar el programa.
	{

		printf("\nError creando el shocket..");
		exit(1);
	}


	printf("\nEl shocket ha sido creado.\n");


	server_addr.sin_family = AF_INET; //tipo de direccin
	server_addr.sin_addr.s_addr = htons(INADDR_ANY); //INADDR_ANY es la IP del host/ordenador que corre el programa
	server_addr.sin_port = htons(Nport); //htons convierte el numero de puerto a orden de bytes de red.


	//2. Bind


	int tryBind = bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr));
	if (tryBind < 0) //En caso de fallo, devolver -1
	{

		printf("Error. Este shocket ya esta en uso..");
		return -1;
	}


	size = sizeof(server_addr);

	puts("Esperando conexion de usuario..");

	//3. Listen

	listen(client, 1); //1 = numero maximo de conexiones simultneas que aceptara el socket


	server = accept(client,(struct sockaddr *)&server_addr,&size); //Pausa el proceso hasta que se conecte alguien, entonces lo retoma


	if (server < 0) //En caso de fallo, devolver -1

		printf("Error al aceptar la conexion.");

	while (server > 0)   //La conexion se ha realizado correctamente
	{
		strcpy(buffer, "Server conectado!\n");
		send(server, buffer, bffSize, 0);


		printf("Conectado con el usuario!");
		printf("\nRecuerda poner & para terminar la conexion.\n"); //Escribir & para poner a true goOut y salir del bucle 

		//4. Bucle que se repite hasta que goOut sea true 

		printf("Usuario: ");
		do {
			recv(server, buffer, bffSize, 0); //recibe el mensaje almacenado en el buffer
			printf("%s", buffer);
			if (*buffer == '&') {
				*buffer = '*';
				goOut = true;
			}

		} while (*buffer != '*');

		do {

			printf("\nServer: ");
			do {
				scanf("%s", buffer);  //Guarda el mensaje en el buffer
				send(server, buffer, bffSize, 0); //y lo envia al otro usuario
				if (*buffer == '&') {
					send(server, buffer, bffSize, 0);
					*buffer = '&';
					goOut = true;
				}
			} while (*buffer != '&');


			printf("Usuario: ");
			do {
				recv(server, buffer, bffSize, 0);
				printf("%s", buffer);
				if (*buffer == '&') {
					*buffer = '*';
					goOut = true;
				}

			} while (*buffer != '&');
		} while (!goOut);


		//5. goOut = true, cerramos la conexin

		printf("\n\nConexion terminada.");
		close(server);
		goOut = false;
		exit(1);
	}

	close(client);
	return 0;
}

