/*
 ============================================================================
 Name        : conexionConNodos.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <unistd.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>
#include "consola.h"

#define PORT 9000

int conexionConNodos(argv) {
	extern t_list* listaNodos_limbo;
	//t_config *config;
	int listener; 							/* listener = fd del socket que genera para escuchar */
	fd_set readfd;							/* Socket file descriptors we want to wake up for, using select() */
	int highsock;							/* Highest #'d file descriptor, needed for select() */
	struct timeval timeout; 				/* Timeout for select */
	int readsocks;	     					/* Number of sockets ready for reading */
	int new_fd;								/* Socket creado al aceptar conexiones */
	struct sockaddr_in their_addr;
	int addrlen;
	
	/*********************************************************************************************************/

	// config = readConfigurationFile(argv);


	listener = initListener(PORT);			/* Creo el socket listener */

	FD_ZERO(&readfd);						/* Inicializo la coleccion con 0s */
	FD_SET(listener,&readfd);				/* Agrego a la coleccion el socket listener */
		/* FD_SET() adds the file descriptor "listener" to the fd_set,
		so that select() will return if a connection comes in
		on that socket (which means you have to do accept(), etc. */

	highsock = listener;
	timeout.tv_sec = 2;
    timeout.tv_usec = 500000;
    
    readsocks = select(highsock+1, &readfd, NULL, NULL, &timeout);

	if (readsocks < 0) {
		perror("select");
		exit(EXIT_FAILURE);
	}
	if (readsocks == 0) {
		/* Nothing ready to read, just show that we're alive */
		printf("NO HAY SOCKET ACTIVO");
		fflush(stdout);
	}else{
		if (FD_ISSET(listener,&readfd)) {
			/* Si el socket que se 'desperto' es el listener, entonces tengo que aceptar la nueva conexion */
			addrlen = sizeof(their_addr);
			new_fd = accept(listener, (struct sockaddr *)&their_addr, (socklen_t *)&addrlen);
			FD_SET (new_fd, &readfd);	/* Agrego el nuevo socket a la coleccion de sockets readable */

			//agrego ip-puerto del nodo a la lista
			list_add(listaNodos_limbo, &their_addr);
		}

		printf("LA IP DEL CLIENTE ES: %s\n", inet_ntoa(their_addr.sin_addr));
	}
	/* Hasta aca estaria cubierto el tema de agregar conexiones entrantes nuevas con el Select,
	 * ya que solo preguntamos con FD_ISSET por el listener (ver primer parametro de la funcion).
	 * Para enviar y recibir datos habria que preguntar, si entendi bien, por los otros sockets que
	 * estan en la coleccion. VER EJEMPLO BEEJ
	 */

	
	return EXIT_SUCCESS;
}


int validarNodosMinimos(void) {
	extern int cantNodosMinimos;
	extern t_list* listaNodos_ok;
	if( cantNodosMinimos <= list_size(listaNodos_ok) )
		return 1;
	else
		return 0;
}

