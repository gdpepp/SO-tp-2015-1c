/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <commons/config.h>
#include <commons/string.h>
#include "general.h"

char* getAppPath(const char* app_call){
	char abs_exe_path[PATH_MAX];
	char path_save[PATH_MAX];
	char *p;

	if(!(p = strrchr(app_call, '/')))
		getcwd(abs_exe_path, sizeof(abs_exe_path));
	else{
		*p = '\0';
		getcwd(path_save, sizeof(path_save));
		chdir(app_call);
		getcwd(abs_exe_path, sizeof(abs_exe_path));
		chdir(path_save);
	}
	return abs_exe_path;
}

t_config* readConfigurationFile(char **argv) {
	char* config_path = string_new();
	string_append(&config_path, getAppPath(argv[0]));
	string_append(&config_path, "/config.cfg");
	t_config *config;

	if( access( config_path, F_OK ) == -1 ){
		perror("config_path"); // Error de acceso al archivo
		exit(1);
	}

	config = config_create(config_path);
	free(config_path);
	return config;
}
