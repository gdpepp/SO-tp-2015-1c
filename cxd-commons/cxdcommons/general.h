/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_GENERAL_H_
#define CXD_GENERAL_H_

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

#endif
