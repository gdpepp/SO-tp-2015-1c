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

void f_thread_escuchas(void* param){
	extern t_list* listaNodos_limbo;
	int port, listener, fdmax, i;
	int fd_marta = 666;
	int new_fd, addrlen;
	fd_set read_fds;
	struct sockaddr_in their_addr;
	t_msjcxd* mensaje_recv;
	t_nodo* nodo;
	t_config* config;
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
					// ... (seguramente un nuevo thread)
				}else{ // posible mensaje
					mensaje_recv = recvMsj(i);
					if( strcmp(mensaje_recv->action, "conexion_cerrada") != 0 ){ // tenemos mensaje de nodo
						if( strcmp(mensaje_recv->action, "inicio_conexion") != 0 ){
							nodo = malloc(sizeof(t_nodo));
							nodo->fichero = i;
							strcpy(nodo->ip, dictionary_get(mensaje_recv->properties, "ip"));
							strcpy(nodo->nodo_nuevo, dictionary_get(mensaje_recv->properties, "nodo_nuevo"));
							// ... (abierto a nuevos parametros de nodo)

							if( strcmp(nodo->nodo_nuevo, "SI") ){
								// agrego nodo a la lista temporal
								list_add(listaNodos_limbo, nodo);
							}else{
								// tratamiento de resureccion de nodo.
							}
							free(nodo);
						}else if( strcmp(mensaje_recv->action, "conexion_marta") != 0 ){
							fd_marta = i; // identificacion del fichero de MaRTA
						}
					}else{ // conexión cerrada por el nodo
						close(i);
						FD_CLR(i, &read_fds);
					}
					free(mensaje_recv);
				}
			}
		}
	}
}
