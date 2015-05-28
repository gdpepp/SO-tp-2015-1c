/*
 ============================================================================
 Name        : MaRTA.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : MapReduceTaskAdministrator
 ============================================================================
 */

#include "thread_job.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <commons/string.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>

#define PUERTO_JOBS 9000

int main(int argc, char **argv) {
	t_config *config;
	fd_set read_fds;
	int listener_jobs, newjob, fdmax, addrlen, i, iret, port_fs;
	char* ip_fs;
	struct sockaddr_in remoteaddr;
	pthread_t thread;
	t_arg_thread_job* arg_thread_job;
	arg_thread_job = malloc(sizeof(t_arg_thread_job));

	config = readConfigurationFile(argv);

	FD_ZERO(&read_fds);

	listener_jobs = initListener(PUERTO_JOBS);
	FD_SET(listener_jobs, &read_fds);
	fdmax = listener_jobs;

	ip_fs = config_get_string_value(config, "IP_FS");
	port_fs = config_get_int_value(config, "PUERTO_FS");

	for(;;){
		if( select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1 ){
			perror("select");
			exit(1);
		}

		for(i = 0; i <= fdmax; i++){
			if( FD_ISSET(i, &read_fds) ){
				if( i == listener_jobs ){
					// nueva conexion de un job
					addrlen = sizeof(remoteaddr);
					if( ( newjob = accept(listener_jobs, (struct sockaddr *)&remoteaddr, (socklen_t *)&addrlen) ) == -1 ){
						perror("accept");
					}else{
						strcpy(arg_thread_job->ip_filesystem, ip_fs);
						arg_thread_job->port_filesystem = port_fs;
						arg_thread_job->fd_job = newjob;

						iret = pthread_create(&thread, NULL, (void *) &thread_job_function, (void*) arg_thread_job);
						if( iret ){
							fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
							exit(EXIT_FAILURE);
						}
					}
				}
			}
		}
	}

	pthread_join( thread, NULL);
	
	config_destroy(config);
	free(arg_thread_job);
	return EXIT_SUCCESS;
}
