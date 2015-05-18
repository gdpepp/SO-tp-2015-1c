/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include <limits.h>
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
#include "sockets.h"

static char* serial_prop;

int conectarCon(char *ip, int puerto){
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

t_msjcxd *iniciarMsj(const char *action){
	t_msjcxd *msj = malloc(sizeof(t_msjcxd));

	msj->action = strdup(action);
	msj->properties = dictionary_create();
	return msj;
}
int agregarInfo(t_msjcxd *self, char *key, char *value){
	dictionary_put(self->properties, key, value);
	return EXIT_SUCCESS;
}
void _serializarpropiedades(char *key, char *data) {
	serial_prop = string_new();
	string_append_with_format(&serial_prop, "%s=%s;", key, data);
}
char* _serializeMsj(t_msjcxd *self){
	char *buffer = string_new();
	string_append_with_format(&buffer, "a:%s|", self->action);
	string_append_with_format(&buffer, "i:%d|", self->id);

	dictionary_iterator(self->properties, (void*)_serializarpropiedades);
	string_append_with_format(&buffer, "p:[%s]", serial_prop);
	free(serial_prop);
	return buffer;
}
t_msjcxd* _unserializeMsj(char *stream){
	int i, len;
	char *tmp_sincorchetes=string_new();
	t_msjcxd *msj = malloc(sizeof(t_msjcxd));
	char** a_temporal = string_split(stream, "|");
	char** tmp = string_split(a_temporal[0], ":");
	msj->action = strdup(tmp[1]);
	free(tmp);
	char** tmp1 = string_split(a_temporal[1], ":");
	msj->id = atoi(tmp1[1]);
	free(tmp1);
	msj->properties = dictionary_create();

	//quitar a "a_temporal[2]" los corchetes
	len = strlen(a_temporal[2]);
	string_append(&tmp_sincorchetes, string_substring(a_temporal[2], 1, len-1));

	free(a_temporal);
	char** tmp2 = string_split(tmp_sincorchetes, ";");
	free(tmp_sincorchetes);

	for(i=0; tmp2[i]!=NULL; i++){
		if( !string_is_empty(tmp2[i]) ){
			char** keyAndValue = string_split(tmp2[i], "=");
			dictionary_put(msj->properties, keyAndValue[0], keyAndValue[1]);
			free(keyAndValue);
		}
	}
	free(tmp2);

	return msj;
}
