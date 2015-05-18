/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_SOCKETS_H_
#define CXD_SOCKETS_H_

	#include <commons/collections/dictionary.h>

	typedef struct {
		char *action;
		int id;
		t_dictionary *properties;
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
	 * @NAME: cerrarConexion
	 * @DESC: cierra conexion con referenciada a el fichero sockfd
	 * @PARAMS:
	 * 		sockfd - descriptor de fichero
	 */
	void cerrarConexion(int sockfd);

	t_msjcxd *iniciarMsj(const char *action);
	int agregarInfo(t_msjcxd *self, char *key, char *value);

#endif
