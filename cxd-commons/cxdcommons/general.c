/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
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
	int len;
	t_config *config;
	char* config_path = string_new();
	
	string_append(&config_path, getAppPath(argv[0]));
	len = strlen(config_path);
	config_path = string_substring_until(config_path, len-5);
	string_append(&config_path, "/src/config.cfg");
	

	if( access( config_path, F_OK ) == -1 ){
		perror("config_path"); // Error de acceso al archivo
		exit(1);
	}

	config = config_create(config_path);
	free(config_path);
	return config;
}

t_log* iniciarLog(char **argv, char *program_name, bool is_active_console, t_log_level level){
	int len;
	t_log* log;
	char* log_path = string_new();

	string_append(&log_path, getAppPath(argv[0]));
	len = strlen(log_path);
	log_path = string_substring_until(log_path, len-5);
	string_append(&log_path, "/src/log.txt");
	log = log_create(log_path, program_name, is_active_console, level);

	return log;
}
