/*
 ============================================================================
 Name        : opcion1.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description : opcion 1 de consola FileSystem
 ============================================================================
 */

#include <unistd.h>
#include "consola.h"

int formatMDFS(void) {
	pTitulo("Consola de FileSystem");
	pWhiteLine();
	pText("¿Seguro que desea borrar el MDFS?:", 0);
	pOptionLine('y', "Borrar MDFS (no puede deshacerse)");
	pOptionLine('n', "Cerrar programa.");
	pWhiteLine();
	pWhiteLine();
	pLineaDivisora();
	pText("Ingresar opción deseada: \033[s", 3);
	pFinConsola();
	printf("\033[u");
	return EXIT_SUCCESS;
}
