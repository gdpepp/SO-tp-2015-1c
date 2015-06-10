/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_OPCIONESC_H_
#define CXD_OPCIONESC_H_

	// Aca vamos a centrar las funciones que ejecuta la consola, cada opcion va a tener como minimo un file.c

	int formatMDFS(void);
	void ABMArchive(void);
	void ABMDirectory(void);
	void copyFSLocalArchiveToMDFS(void);
	void copyMDFSArchiveToFSLocal(void);
	void archiveMD5(void);
	void ABMArchiveBlocks(void);
	void addNode(void);
	void deleteNode(void);

#endif
