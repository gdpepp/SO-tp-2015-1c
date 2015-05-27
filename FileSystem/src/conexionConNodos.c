#include <unistd.h>
#include "consola.h"
#include <commons/string.h>
#include <commons/list.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>

int listener; 

int conexionConNodos(argv) {
	
	int port= 9000;
	listener = initListener(port);
		//listener = fd del socket que genera para escuchar
	
	t_config *config = readConfigurationFile(argv);
		
	fd_set selectDescriptors;	
		/* Socket file descriptors we want to wake
		up for, using select() */
		FD_SET(listener,&selectDescriptors);
		/* FD_SET() adds the file descriptor "listener" to the fd_set,
		so that select() will return if a connection comes in
		on that socket (which means you have to do accept(), etc. */
	int highsock;			/* Highest #'d file descriptor, needed for select() */
	struct timeval timeout; /* Timeout for select */
	int readsocks;	     	/* Number of sockets ready for reading */
	


	while (1) { /* Main server loop - forever */
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
	
		readsocks = select(highsock+1, &selectDescriptors, (fd_set *) 0, 
		  (fd_set *) 0, &timeout);
		
		if (readsocks < 0) {
			perror("select");
			exit(EXIT_FAILURE);
		}
		if (readsocks == 0) {
			/* Nothing ready to read, just show that
			   we're alive */
			printf(".");
			fflush(stdout);
		} else
			read_socks();
	} 
	
	FD_ZERO(&selectDescriptors);
		/* FD_ZERO() clears out the fd_set called socks, so that
		it doesn't contain any file descriptors. */

	return EXIT_SUCCESS;
}


void read_socks() {
	int listnum;	     /* Current item in connectlist for for loops */
	
	if (FD_ISSET(listener,&selectDescriptors))
		handleNewConnection();
/*	
	for (listnum = 0; listnum < 5; listnum++) {
		if (FD_ISSET(connectlist[listnum],&socks))
			deal_with_data(listnum);
	} /* for (all entries in queue) 
*/ 
//VER QUE HACE ESTE FOR

}



handleNewConnection() {

	struct sockaddr_in their_addr;

	if ((int socketNodo = accept(listener, their_addr, sizeof(struct sockaddr_in)))) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	list_add(listaNodos, their_addr);
	//agrega la info del nodo a la lista
}