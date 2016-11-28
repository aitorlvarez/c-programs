#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define bffSize 1024


int main(int argc, const char *argv[])
{

	int client;
	int port = 1100;
	bool goOut = false;
	char buffer[bffSize];

	struct sockaddr_in server_addr;


	//Creacin del socket 

	client = socket(AF_INET, SOCK_STREAM, 0);


	if (client < 0) 
	{
		printf("\nError al crear el shocket...");
		exit(1);
	}


	printf("\nEl shocket se ha creado correctamente\n");


	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	//Conexin

	int connection = connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr));

	if (connection == 0)  //En caso de fallo no devolver 0, sino -1

		printf("Conectado por el puerto %i", port);


	recv(client, buffer, bffSize, 0);
	printf("\nConexion establecida.\n");


	do {
		printf("Usuario: ");
		do {
			scanf("%s", buffer);
			send(client, buffer, bffSize, 0);
			if (*buffer == '&') {
				send(client, buffer, bffSize, 0);
				*buffer = '*';
				goOut = true;
			}
		} while (*buffer != '*');

		printf("Server: ");
		do {
			recv(client, buffer, bffSize, 0);
			printf("%s", buffer);
			printf(" ");
			if (*buffer == '&') {
				*buffer = '*';
				goOut = true;
			}

		} while (*buffer != '*');
		printf("\n");

	} while (!goOut);


	//Close

	printf("\nConexin terminada.\n");

	close(client);
	return 0;
}

