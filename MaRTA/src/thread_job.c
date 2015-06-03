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
	//extern pthread_mutex_t pantalla;
	t_msjcxd* mensaje_recv;
	t_msjcxd* mensaje_send;
	t_arg_thread_job* arg;
	arg = (t_arg_thread_job*) param;

	fd_filesystem = conectarCon(arg->ip_filesystem, arg->port_filesystem);

	mensaje_recv = recvMsj(arg->fd_job);
	if( strcmp(mensaje_recv->action, "conexion_cerrada") != 0 ){ // tenemos mensaje de job
		if( strcmp(mensaje_recv->action, "inicio_pedido") != 0 ){
			mensaje_send = iniciarMsj("info_archivo");
			agregarInfo(mensaje_send, "arch_name", dictionary_get(mensaje_recv->properties, "arch_name"));
			sendMsj(mensaje_send, fd_filesystem);
			// ...
		}
	}else{ // conexión cerrada por el job
		// ...
		/*pthread_mutex_lock( &pantalla );
		printf("Conexion cerrada (thread_id: %ld).\n", pthread_self());
		pthread_mutex_unlock( &pantalla );*/
		close(arg->fd_job);
	}
}
