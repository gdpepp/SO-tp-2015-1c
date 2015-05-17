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
#include <commons/config.h>
#include <cxdcommons/general.h>

int main(int argc, char **argv) {
	char* config_path = string_new();
	string_append(&config_path, getAppPath(argv[0]));
	string_append(&config_path, "/config.cfg");

	t_config *config;
	char* ip_fs;
	int puerto_fs;

	if( access( config_path, F_OK ) == -1 ){
		perror("config_path"); // Error de acceso al archivo
		exit(1);
	}

	config = config_create(config_path);
	free(config_path);
	ip_fs = config_get_string_value(config, "IP_FS");
	puerto_fs = config_get_int_value(config, "PUERTO_FS");

	printf("La IP de FS es: %s\n", ip_fs);
	printf("El puerto de FS es: %d\n", puerto_fs);


	config_destroy(config);
	return EXIT_SUCCESS;
}
