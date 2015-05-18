/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#include <limits.h>
#include <string.h>
#include <unistd.h>
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
