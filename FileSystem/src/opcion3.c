/*
 ============================================================================
 Name        : opcion3.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <unistd.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>
#include "consola.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int printConsolaOpcion3();

void opcion3() {

	char opcion;
	char ruta[100], ruta2[100];
	struct stat st = {0};

CONSOLA:
	printConsolaOpcion3();
	opcion = getchar();

	limpiarPantalla();

	if( opcion != '\n' ) {
		switch( opcion ) {
			default:
				printf("Opción incorrecta...\n");
				sleep(1);
				goto CONSOLA;
				break;
		
			case '1':
				printf("ingrese ruta a crear: \n");
				scanf("%s", &ruta);
				if (stat(ruta, &st) == -1) {
					if((mkdir(ruta, 0700)) != -1) {
						printf("Ruta creada correctamente :)\n");
						sleep(1);
					}
					else { 
						fprintf(stderr, "Ruta '%s' no pudo ses creada: %s\n", ruta, strerror(errno));
						sleep(1); 
						goto CONSOLA;
					}
				} else fprintf("La ruta: '%s' definida ya existe. %s\n", ruta, strerror(errno));
				goto CONSOLA;
				break;

			case '2':
				printf("ingrese ruta a eliminar: \n");
				scanf("%s", &ruta);
				if (stat(ruta, &st) == -1) {
					perror("la ruta no existe \n");
					sleep(1);
					goto CONSOLA;
				}
				if((rmdir(ruta)) != -1) {
						printf("Ruta borrada correctamente \n");
						sleep(1);
				}
				else {
					fprintf(stderr, "Ruta '%s' no pudo ser borrada: %s\n", ruta, strerror(errno));
					sleep(1);
				}
					goto CONSOLA;

			case '3':
				printf("ingrese ruta a renombrar: \n");
				scanf("%s", &ruta);
				printf("ingrese la nueva ruta: \n");
				scanf("%s", &ruta);
				if (stat(ruta, &st) == -1) {
					perror("la ruta no existe");
					sleep(1);
					goto CONSOLA;
				}
				if((rename(ruta, ruta2)) != -1) {
					printf("la ruta fue renombrada correctamente \n");
					sleep(1);
				}
				else {
					fprintf("La ruta: '%s' no pudo ser renombrada. %s\n", ruta, strerror(errno));
					sleep(1);
				}
				goto CONSOLA;
		}
	} else 	goto CONSOLA;
}

int printConsolaOpcion3(void) {
	pTitulo("Consola de Filesystem - Crear/Eliminar/Renombrar/Mover un directorio");
	pWhiteLine();
	pOptionLine('1', "Crear directorio");
	pOptionLine('2', "Eliminar directorio");
	pOptionLine('3', "Renombrar/Mover directorio.");
	pOptionLine('q', "Cerrar programa.");
	pWhiteLine();
	pWhiteLine();
	pLineaDivisora();
	pText("Ingresar opción deseada: \033[s", 3);
	pFinConsola();
	printf("\033[u");

	return EXIT_SUCCESS;
}

/*
int getlinea(char* ruta) {
	char c;
	int i;
	fflush(0);
	for(i=0; ((c = getchar()) == '\n'); i++)
		ruta[i] = c;
		return EXIT_SUCCESS;
} */
