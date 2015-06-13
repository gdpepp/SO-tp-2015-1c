/*
 ============================================================================
 Name        : MaRTA.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description : MapReduceTaskAdministrator
 ============================================================================
 */

#include "thread_job.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <commons/config.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>

#define PUERTO_JOBS 9000
pthread_mutex_t pantalla = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pedido_filesystem = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv){
	t_config* config;
	fd_set read_fds;
	int listener_jobs, newjob, fdmax, addrlen, iret;
	int fd_filesystem;
	t_msjcxd* mensaje_send;
	struct sockaddr_in remoteaddr;
	pthread_t thread;
	t_arg_thread_job* arg_thread_job;

	config = readConfigurationFile(argv);

	FD_ZERO(&read_fds);

	listener_jobs = initListener(PUERTO_JOBS);
	FD_SET(listener_jobs, &read_fds);
	fdmax = listener_jobs;

	fd_filesystem = conectarCon(config_get_string_value(config, "IP_FILESYSTEM"), config_get_int_value(config, "PUERTO_FILESYSTEM"));
	mensaje_send = iniciarMsj("conexion_marta");
	sendMsj(mensaje_send, fd_filesystem);

	for(;;){
		if( select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1 ){
			perror("select");
			exit(1);
		}
		if( FD_ISSET(listener_jobs, &read_fds) ){ // nueva conexion de un job
			addrlen = sizeof(remoteaddr);
			if( ( newjob = accept(listener_jobs, (struct sockaddr *)&remoteaddr, (socklen_t *)&addrlen) ) == -1 ){
				perror("accept");
			}else{
				arg_thread_job = malloc(sizeof(t_arg_thread_job));
				arg_thread_job->fd_filesystem = fd_filesystem;
				arg_thread_job->fd_job = newjob;

				iret = pthread_create(&thread, NULL, (void *) &thread_job_function, (void*) arg_thread_job);
				if( iret ){
					fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
					exit(EXIT_FAILURE);
				}
				free(arg_thread_job);
			}
		}
	}

	pthread_join( thread, NULL);
	
	config_destroy(config);
	return EXIT_SUCCESS;
}
