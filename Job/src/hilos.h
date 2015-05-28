/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_HILO_H_
#define CXD_HILO_H_

	#include <pthread.h>

	typedef struct {

	} t_arg_hilo_mapper;

	typedef struct {

	} t_arg_hilo_reduce;

	void hilo_mapper_function(void* param);
	void hilo_reduce_function(void* param);

#endif
