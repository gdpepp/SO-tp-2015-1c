#include <unistd.h>
#include "consola.h"
#include <commons/string.h>
#include <commons/list.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>


int conexionConNodos(argv) {
	
	t_list listaNodos = list_create();

	int socketNodo;
	int listener;
	int port= 9000;
	t_config *config = readConfigurationFile(argv);
	t_listaNodos *infoNodo = malloc(sizeof(t_listaNodos));
	
listener = initListener(port);
//listener = fd del socket que genera para escuchar

socketNodo = accept(listener, t_listaNodos->their_addr, sizeof(struct sockaddr_in));

t_listaNodos->ipNodo = their_addr->

	return EXIT_SUCCESS;
}
