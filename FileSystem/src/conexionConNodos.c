#include <unistd.h>
#include "consola.h"
#include <commons/string.h>
#include <commons/list.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>


int conexionConNodos(argv) {
	
	t_config *config = readConfigurationFile(argv);
		
	fd_set selectDescriptors;	
		/* Socket file descriptors we want to wake
		up for, using select() */
	FD_ZERO(&selectDescriptors);
		/* FD_ZERO() clears out the fd_set called socks, so that
		it doesn't contain any file descriptors. */
	FD_SET(socketNodo,&socketNodo);
		/* FD_SET() adds the file descriptor "socketNodo" to the fd_set,
		so that select() will return if a connection comes in
		on that socket (which means you have to do accept(), etc. */
	int highsock;			/* Highest #'d file descriptor, needed for select() */
	struct timeval timeout; /* Timeout for select */
	int readsocks;	     	/* Number of sockets ready for reading */
	
	handleNewConnection();


	while (1) { /* Main server loop - forever */
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		/* The first argument to select is the highest file
			descriptor value plus 1. In most cases, you can
			just pass FD_SETSIZE and you'll be fine. */
			
		/* The second argument to select() is the address of
			the fd_set that contains sockets we're waiting
			to be readable (including the listening socket). */
			
		/* The third parameter is an fd_set that you want to
			know if you can write on -- this example doesn't
			use it, so it passes 0, or NULL. The fourth parameter
			is sockets you're waiting for out-of-band data for,
			which usually, you're not. */
		
		/* The last parameter to select() is a time-out of how
			long select() should block. If you want to wait forever
			until something happens on a socket, you'll probably
			want to pass NULL. */
		
		readsocks = select(highsock+1, &socks, (fd_set *) 0, 
		  (fd_set *) 0, &timeout);
		
		/* select() returns the number of sockets that had
			things going on with them -- i.e. they're readable. */
			
		/* Once select() returns, the original fd_set has been
			modified so it now reflects the state of why select()
			woke up. i.e. If file descriptor 4 was originally in
			the fd_set, and then it became readable, the fd_set
			contains file descriptor 4 in it. */
		
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
	} /* while(1) */
} /* main */

	return EXIT_SUCCESS;
}


handleNewConnection() {

	int listener;
	int port= 9000;
	listener = initListener(port);
		//listener = fd del socket que genera para escuchar

	struct sockaddr_in their_addr;

	if ((socketNodo = accept(listener, their_addr, sizeof(struct sockaddr_in)))) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	list_add(listaNodos, their_addr);
	//agrega la info del nodo a la lista
}