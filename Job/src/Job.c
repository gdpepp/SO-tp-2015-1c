/*
 ============================================================================
 Name        : Job.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description : Job
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>
#include "hilos.h"

int main(int argc, char **argv) {
	t_config *config;
	int fd_marta, fdmax, iret;
	//t_msjcxd* mensaje_recv;
	t_msjcxd* mensaje_send;
	fd_set read_fds;
	pthread_t thread;
	t_arg_hilo_mapper* arg_hilo_mapper;
	arg_hilo_mapper = malloc(sizeof(t_arg_hilo_mapper));
	t_arg_hilo_reduce* arg_hilo_reduce;
	arg_hilo_reduce = malloc(sizeof(t_arg_hilo_reduce));

	config = readConfigurationFile(argv);

	FD_ZERO(&read_fds);
	fd_marta = conectarCon(config_get_string_value(config, "IP_MARTA"), config_get_int_value(config, "PUERTO_MARTA"));
	fdmax = fd_marta;
	FD_SET(fd_marta, &read_fds);

	mensaje_send = iniciarMsj("inicio_pedido");
	agregarInfo(mensaje_send, "arch_name", config_get_string_value(config, "ARCHIVO"));
	agregarInfo(mensaje_send, "combiner", config_get_string_value(config, "COMBINER"));
	agregarInfo(mensaje_send, "mapper", config_get_string_value(config, "MAPPER"));
	agregarInfo(mensaje_send, "reduce", config_get_string_value(config, "REDUCE"));
	sendMsj(mensaje_send, fd_marta);

	for(;;){
		if( select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1 ){
			perror("select");
			exit(1);
		}
		if( FD_ISSET(fd_marta, &read_fds) ){
			// if hilo mapper
			iret = pthread_create(&thread, NULL, (void*) &hilo_mapper_function, (void*) arg_hilo_mapper);
			if( iret ){
				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
				exit(EXIT_FAILURE);
			}
			// if ok_mapper
			break;
		}
	}
	for(;;){
		if( select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1 ){
			perror("select");
			exit(1);
		}
		if( FD_ISSET(fd_marta, &read_fds) ){
			// if hilo reduce
			iret = pthread_create(&thread, NULL, (void*) &hilo_reduce_function, (void*) arg_hilo_reduce);
			if( iret ){
				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
				exit(EXIT_FAILURE);
			}
			// if ok_reduce (MaRTA solicita a FS copiar el archivo de resultado al MDFS y avisa al Job el resultado de esa operacion.)
			break;
		}
	}

	// Mostrar datos del proceso Job en pantalla y/o archivo de log (ver tabla pag 10).

	return EXIT_SUCCESS;
}
