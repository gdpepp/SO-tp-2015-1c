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
	
	t_config *config;
	int listener; 							/* listener = fd del socket que genera para escuchar */
	fd_set readfd;							/* Socket file descriptors we want to wake up for, using select() */
	int highsock;							/* Highest #'d file descriptor, needed for select() */
	struct timeval timeout; 				/* Timeout for select */
	int readsocks;	     					/* Number of sockets ready for reading */
	int new_fd;								/* Socket creado al aceptar conexiones */
	struct sockaddr_in their_addr;
	
	/*********************************************************************************************************/

		/* config = readConfigurationFile(argv); */


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
			/* Nothing ready to read, just show that
			   we're alive */
			printf("NO HAY SOCKET ACTIVO");
			fflush(stdout);
		} else
			if (FD_ISSET(listener,&readfd)) {

				/* Si el socket que se 'desperto' es el listener, entonces tengo que aceptar la nueva conexion */
				new_fd = accept(listener, (struct sockaddr *)&their_addr, sizeof their_addr);
				FD_SET (new_fd, &readfd);	/* Agrego el nuevo socket a la coleccion de sockets readable */

			}

		printf ("LA IP DEL CLIENTE ES: ");
		printf (inet_ntoa(their_addr.sin_addr));

		/* Hasta aca estaria cubierto el tema de agregar conexiones entrantes nuevas con el Select,
		 * ya que solo preguntamos con FD_ISSET por el listener (ver primer parametro de la funcion).
		 * Para enviar y recibir datos habria que preguntar, si entendi bien, por los otros sockets que
		 * estan en la coleccion. VER EJEMPLO BEEJ
		 */

	
	return EXIT_SUCCESS;
}



/*

handleNewConnection() {

	struct sockaddr_in their_addr;

	if ((int socketNodo = accept(listener, their_addr, sizeof(struct sockaddr_in)))) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	list_add(listaNodos, their_addr);
	//agrega la info del nodo a la lista
}

*/
