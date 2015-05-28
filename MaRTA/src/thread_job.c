/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include "thread_job.h"
#include <limits.h>
#include <stdio.h>
#include <commons/string.h>
#include <cxdcommons/sockets.h>

void thread_job_function(void* param){
	int fd_filesystem;
	t_msjcxd* mensaje_recv;
	t_msjcxd* mensaje_send;
	t_arg_thread_job* arg;
	arg = (t_arg_thread_job*) param;

	fd_filesystem = conectarCon(arg->ip_filesystem, arg->port_filesystem);

	mensaje_recv = recvMsj(arg->fd_job);
	if( strcmp(mensaje_recv->action, "conexion_cerrada") != 0 ){ // tenemos mensaje de job
		mensaje_send = iniciarMsj("info_archivo");
		agregarInfo(mensaje_send, "arch_name", dictionary_get(mensaje_recv->properties, "arch_name"));
		sendMsj(mensaje_send, fd_filesystem);
		// ...
	}else{ // conexión cerrada por el job
		// ...
		close(arg->fd_job);
	}
}
