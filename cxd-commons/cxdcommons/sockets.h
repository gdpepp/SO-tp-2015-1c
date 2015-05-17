/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_SOCKETS_H_
#define CXD_SOCKETS_H_

	/**
	 * @NAME: conectarCon
	 * @DESC: realiza la conexion con un proceso y retorna el descriptor
	 *		de fichero utilizado
	 * @PARAMS:
	 * 		ip - IP del proceso al que te vas a conectar
	 *		puerto - Puerto que esta escuchando dicho proceso
	 */
	int conectarCon(char* ip, int puerto);

#endif
