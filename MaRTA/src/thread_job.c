/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include "thread_job.h"
#include <limits.h>
#include <cxdcommons/sockets.h>

void thread_job_function(void* param){
	int fd_filesystem, nbytes;
	char* buf[CHAR_MAX];
	t_arg_thread_job* arg;
	arg = (t_arg_thread_job*) param;

	fd_filesystem = conectarCon(arg->ip_filesystem, arg->port_filesystem);

	if( (nbytes = recv(arg->fd_job, buf, sizeof(buf), 0)) > 0 ){ // tenemos mensaje de job
		// ...
	}else{ // error o conexión cerrada por el job
		if( nbytes == -1 ){ // conexión cerrada
			perror("recv");
		}else if( nbytes == 0 ){
			// ajam
		}
		close(arg->fd_job);
	}
}
