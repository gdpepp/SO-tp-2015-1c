/*
 * thread_escuchas.c
 *
 *  Created on: 3/6/2015
 *      Author: ezeyuske
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thread_escuchas.h"
#include <commons/string.h>
#include <cxdcommons/general.h>

static bool nodoPorFichero(void *param, void* argumento);
static bool nodoPorNombre(void *param, void* argumento);
static bool existeNodo( t_nodo_fs* nodo );

void f_thread_escuchas(void* param){
	extern t_list* listaNodos_limbo;
	extern t_list* listaNodos_ok;
	extern pthread_mutex_t log_file;
	extern t_log* logger;

	int port, listener, fdmax, i;
	int fd_marta = 666;
	int new_fd, addrlen, iret2;
	int index;
	t_link_element *element;
	fd_set read_fds;
	struct sockaddr_in their_addr;
	t_nodo_fs* nodo;
	t_config* config;
	t_msjcxd* mensaje_send;
	t_msjcxd* mensaje_recv;
	pthread_t thread_pedidosmarta;
	t_arg_pedidomarta* arg_hilo_marta;
	arg_hilo_marta = malloc(sizeof(t_arg_pedidomarta));
	config = (t_config*) param;

	port = config_get_int_value(config, "PUERTO_LISTEN");

	FD_ZERO(&read_fds);

	listener = initListener(port);
	FD_SET(listener, &read_fds);
	fdmax = listener;

	for(;;){
		if( select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1 ){
			perror("select");
			exit(1);
		}
		for(i = 0; i <= fdmax; i++){
			if( FD_ISSET(i, &read_fds) ){
				if( i == listener ){ // nueva conexion
					addrlen = sizeof(their_addr);
					if( ( new_fd = accept(listener, (struct sockaddr *)&their_addr, (socklen_t *)&addrlen) ) == -1 ){
						perror("accept");
					}
					FD_SET(new_fd, &read_fds);
					if( fdmax < new_fd )
						fdmax = new_fd;
				}else if( i == fd_marta ){ // pedido MaRTA
					arg_hilo_marta->fd_marta = fd_marta;
					arg_hilo_marta->mensaje_recv = recvMsj(fd_marta);
					iret2 = pthread_create(&thread_pedidosmarta, NULL, (void *) &f_thread_pedidosmarta, (void*) arg_hilo_marta);
					if( iret2 ){
						fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
						exit(EXIT_FAILURE);
					}
					pthread_mutex_lock( &log_file );
					log_info(logger, "MaRTA pidio lista de bloque del archivo %s.", dictionary_get(mensaje_recv->properties, "arch_name"));
					pthread_mutex_unlock( &log_file );
				}else{ // posible mensaje
					mensaje_recv = recvMsj(i);
					if( strcmp(mensaje_recv->action, "conexion_cerrada") != 0 ){ // tenemos mensaje de nodo
						if( strcmp(mensaje_recv->action, "inicio_conexion") == 0 ){
							nodo = malloc(sizeof(t_nodo_fs));
							nodo->fichero = i;
							strcpy(nodo->ip, dictionary_get(mensaje_recv->properties, "ip"));
							strcpy(nodo->nodo_nuevo, dictionary_get(mensaje_recv->properties, "nodo_nuevo"));
							strcpy(nodo->nombre, dictionary_get(mensaje_recv->properties, "nombre"));
							// abierto a nuevos parametros de nodo...
							
							if( strcmp(nodo->nodo_nuevo, "SI") == 0 ){ // agrego nodo a la lista temporal
								if( existeNodo( nodo ) ){
									// envia msj a nodo informando duplicado y cierra conexión
									mensaje_send = iniciarMsj("nodo_duplicado");
									sendMsj(mensaje_send, i);
									close(i);
									FD_CLR(i, &read_fds);
									pthread_mutex_lock( &log_file );
									log_warning(logger, "Se desconecto a un nodo duplicado.");
									pthread_mutex_unlock( &log_file );
								}else{
									list_add(listaNodos_limbo, nodo);
									pthread_mutex_lock( &log_file );
									log_info(logger, "Se conecto un nuevo nodo.");
									pthread_mutex_unlock( &log_file );
								}
							}else{ // tratamiento de resureccion de nodo.
								/* (tratamiento de mongoDB) */
								list_add(listaNodos_ok, nodo);
								pthread_mutex_lock( &log_file );
								log_info(logger, "Se conecto un nodo ya existente.");
								pthread_mutex_unlock( &log_file );
							}
							free(nodo);
						}else if( strcmp(mensaje_recv->action, "conexion_marta") == 0 ){
							fd_marta = i; // identificacion del fichero de MaRTA
							pthread_mutex_lock( &log_file );
							log_info(logger, "Se conecto MaRTA.");
							pthread_mutex_unlock( &log_file );
						}
					}else{ // conexión cerrada por el nodo o MaRTA
						if( i != fd_marta ){
							element = list_find_element(listaNodos_limbo, nodoPorFichero, &index, (void*) &i);
							if( element != NULL ){
								list_remove(listaNodos_limbo, index);
							}else{
								element = list_find_element(listaNodos_ok, nodoPorFichero, &index, (void*) &i);
								if( element != NULL ){
									list_remove(listaNodos_ok, index);
									/* (tratamiento de mongoDB) */
								}
							}
							close(i);
							FD_CLR(i, &read_fds);
							pthread_mutex_lock( &log_file );
							log_info(logger, "Se desconecto un nodo.");
							pthread_mutex_unlock( &log_file );
						}else{
							// se deconecto MaRTA :S
							/* (...) */
							close(fd_marta);
							FD_CLR(fd_marta, &read_fds);
							pthread_mutex_lock( &log_file );
							log_info(logger, "Se desconecto MaRTA.");
							pthread_mutex_unlock( &log_file );
						}
					}
					free(mensaje_recv);
				}
			}
		}
	}
	pthread_join( thread_pedidosmarta, NULL);
}

t_link_element* list_find_element(t_list *self, bool(*condition)(void*, void*), int* index, void* argumento) {
	t_link_element *element = self->head;
	int position = 0;

	while (element != NULL && !condition(element->data, argumento)) {
		element = element->next;
		position++;
	}

	if (index != NULL) {
		*index = position;
	}

	return element;
}

static bool nodoPorFichero(void *param, void* argumento){
	int fichero_a_buscar;
	t_nodo_fs* nodo;
	nodo = (t_nodo_fs*) param;
	fichero_a_buscar = (int) argumento;
	if( nodo->fichero == fichero_a_buscar )
		return true;
	return false;
}
static bool nodoPorNombre(void *param, void* argumento){
	char* nombre;
	t_nodo_fs* nodo;
	nodo = (t_nodo_fs*) param;
	nombre = string_new();
	string_append(&nombre, (char*) argumento);

	if( strcmp(nodo->nombre, nombre) == 0 )
		return true;
	return false;
}
static bool existeNodo( t_nodo_fs* nodo ){
	extern t_list* listaNodos_limbo;
	extern t_list* listaNodos_ok;
	t_link_element *element;
	int index;
	element = list_find_element(listaNodos_limbo, nodoPorNombre, &index, nodo->nombre);
	if( element != NULL )
		return true;
	
	element = list_find_element(listaNodos_ok, nodoPorNombre, &index, nodo->nombre);
	if( element != NULL )
		return true;
	
	return false;
}
