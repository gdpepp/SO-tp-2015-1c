/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_GENERAL_H_
#define CXD_GENERAL_H_

	#include <commons/log.h>

	/**
	 * @NAME: getAppPath
	 * @DESC: Devuelve ruta absoluta del ejecutable
	 * @PARAMS:
	 * 		app_call - se ingresa el argv[0] del "main(int argc, char **argv)"
	 */
	char* getAppPath(const char* app_call);

	/**
	 * @NAME: readConfigurationFile
	 * @DESC: Lee el archivo configuracion ubicado en la misma ruta que el ejecutable
	 * @PARAMS:
	 * 		argv - parametro de main
	 */
	t_config* readConfigurationFile(char **argv);

	/**
	 * @NAME: iniciarLog
	 * @DESC: inicia el archivo log
	 * @PARAMS:
	 * 		argv - parametro de main
	 * 		program_name - nombre del programa
	 * 		is_active_console - si se imprime en pantalla
	 * 		level - nivel de detalle minimo a loguear
	 */
	t_log* iniciarLog(char **argv, char *program_name, bool is_active_console, t_log_level level);

#endif
