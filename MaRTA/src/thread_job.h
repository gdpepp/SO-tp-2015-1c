/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef THREAD_JOB_H_
#define THREAD_JOB_H_

	#include <string.h>
	#include <pthread.h>

	typedef struct {
		char ip_filesystem[16];
		int port_filesystem;
		int fd_job;
	} t_arg_thread_job;

	void thread_job_function(void* param);

#endif
