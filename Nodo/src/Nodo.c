/*
 ============================================================================
 Name        : Nodo.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description : Nodo
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/config.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>

int main(int argc, char **argv) {
	int fd_filesystem;
	t_config *config;
	t_msjcxd* mensaje_send;

	config = readConfigurationFile(argv);

	/* seteo ARCHIVO_BIN y DIR_TEMP */

	fd_filesystem = conectarCon(config_get_string_value(config, "IP_FS"), config_get_int_value(config, "PUERTO_FS"));
	mensaje_send = iniciarMsj("inicio_conexion");
	agregarInfo(mensaje_send, "ip", config_get_string_value(config, "IP_NODO"));
	agregarInfo(mensaje_send, "nuevo_nodo", config_get_string_value(config, "NODO_NUEVO"));
	agregarInfo(mensaje_send, "nombre", config_get_string_value(config, "NOMBRE"));
	sendMsj(mensaje_send, fd_filesystem);

	/* escuchas de acciones FS y conexiones y pedidos de otros Nodos */

	return EXIT_SUCCESS;
}
