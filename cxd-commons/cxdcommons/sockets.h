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
	 * @NAME: initListener
	 * @DESC: inicia fichero para escuchar conexiones
	 * @PARAMS:
	 * 		port - puerto por el cual se escuchan las conexiones
	 */
	int initListener(int port);

	/**
	 * @NAME: iniciarConjuntosFicheros
	 * @DESC: como dice el nombre de la función, inicializa los conjuntos de ficheros
	 */
	void iniciarConjuntosFicheros(void);

	/**
	 * @NAME: agregarFichero
	 * @DESC: agregar fichero al conjuto maestro de ficheros
	 * @PARAMS:
	 * 		fichero - fichero a agregar
	 */
	void agregarFichero(int fichero);

	/**
	 * @NAME: cerrarConexion
	 * @DESC: cierra conexion con el fichero sockfd y lo quita del conjunto maestro
	 *		de ficheros si esta
	 * @PARAMS:
	 * 		sockfd - descriptor de fichero
	 */
	void cerrarConexion(int sockfd);

	t_msjcxd *iniciarMsj(const char *action);
	int agregarInfo(t_msjcxd *self, char *key, char *value);

#endif
