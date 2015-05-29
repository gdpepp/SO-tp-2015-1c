/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_HILO_H_
#define CXD_HILO_H_

	#include <pthread.h>

 	typedef struct {
 		char name[8];
		char ip[16];
		int port;
 	} t_nodo;

 	typedef struct {
		t_nodo nodo;
		int bloque;
		void* script_mapper; // sin definir el tipo
		char* arch_result_name;
		int fd_marta;
	} t_arg_hilo_mapper;

	typedef struct {
		void* script_reduce; // sin definir el tipo
		int fd_marta;
	} t_arg_hilo_reduce;

	void hilo_mapper_function(void* param);
	void hilo_reduce_function(void* param);

#endif
