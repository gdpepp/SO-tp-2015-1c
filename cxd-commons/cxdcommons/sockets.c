/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <commons/string.h>

int conectarCon(char* ip, int puerto){
	int sockfd;
	struct hostent *he;
	struct sockaddr_in their_addr; // información de la dirección de destino

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		perror("socket");
		exit(1);
	}
	if( (he=gethostbyname(ip)) == NULL ){ // obtener información de máquina
		perror("gethostbyname");
		exit(1);
	}
	their_addr.sin_family = AF_INET;  // Ordenación de bytes de la máquina
	their_addr.sin_port = htons(puerto); // short, Ordenación de bytes de la red
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la  estructura
	if( connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1 ){
		perror("connect");
		exit(1);
	}
	return sockfd;
}
void cerrarConexion(int sockfd){
	close(sockfd);
}
char* _serializeMsj(void){
	char* buffer = string_new();
	return buffer;
}
void _unserializeMsj(char* stream){}
