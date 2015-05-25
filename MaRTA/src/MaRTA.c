/*
 ============================================================================
 Name        : MaRTA.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : MapReduceTaskAdministrator
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <commons/string.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>

#define PUERTO_JOBS 9000

int main(int argc, char **argv) {
	t_config *config;
	fd_set master, read_fds;
	int fd_fs, listener_jobs, newjob, fdmax, addrlen, nbytes, i;
	char buf[256];
	struct sockaddr_in remoteaddr;

	config = readConfigurationFile(argv);

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	listener_jobs = initListener(PUERTO_JOBS);
	FD_SET(listener_jobs, &master);
	fdmax = listener_jobs;

	fd_fs = conectarCon(config_get_string_value(config, "IP_FS"), config_get_int_value(config, "PUERTO_FS"));
	FD_SET(fd_fs, &master);
	if( fd_fs > fdmax )
		fdmax = fd_fs;

	// version sin hilos, hay que analizar donde empezar a meter los hilos
	for(;;){
		read_fds = master;
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
						FD_SET(newjob, &master);
						if( newjob > fdmax )
							fdmax = newjob;
					}
				}else if( i == fd_fs ){
					// FileSystem
					if( (nbytes = recv(fd_fs, buf, sizeof(buf), 0)) <= 0 ){ // error o conexión cerrada por el FS
						if( nbytes == 0 ){ // conexión cerrada
							// aqui deberia volver a conectar
						}else{
							perror("recv");
						}
						close(fd_fs);
						FD_CLR(fd_fs, &master);
					}else{
						// tenemos mensaje de FS
					}
				}else{
					// Job
					if( (nbytes = recv(i, buf, sizeof(buf), 0)) <= 0 ){ // error o conexión cerrada por el job
						if( nbytes == 0 ){ // conexión cerrada
							// ajam
						}else{
							perror("recv");
						}
						close(i);
						FD_CLR(i, &master);
					}else{
						// tenemos mensaje de algun job
					}
				}
			}
		}
	}
	
	config_destroy(config);
	return EXIT_SUCCESS;
}
