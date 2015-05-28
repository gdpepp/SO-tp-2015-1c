/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_SOCKETS_H_
#define CXD_SOCKETS_H_

	#include <netdb.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <commons/collections/dictionary.h>

	typedef struct {
		char* action;
		int id;
		t_dictionary* properties;
	} t_msjcxd;

	/**
	 * @NAME: conectarCon
	 * @DESC: realiza la conexion con un proceso y retorna el descriptor
	 *		de fichero utilizado
	 * @PARAMS:
	 * 		ip - IP del proceso al que te vas a conectar
	 *		puerto - Puerto que esta escuchando dicho proceso
	 */
	int conectarCon(char* ip, int puerto);

	/**
	 * @NAME: initListener
	 * @DESC: inicia fichero para escuchar conexiones
	 * @PARAMS:
	 * 		port - puerto por el cual se escuchan las conexiones
	 */
	int initListener(int port);

	t_msjcxd *iniciarMsj(const char *action);
	int agregarInfo(t_msjcxd *self, const char *key, const char *value);
	void sendMsj(t_msjcxd* self, int fichero);
	t_msjcxd* recvMsj(int fichero);

#endif
