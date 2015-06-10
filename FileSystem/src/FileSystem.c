 /*
 ============================================================================
 Name        : FileSystem.c
 Author      : Compilo x Dinero
 Version     :
 Copyright   : Your copyright notice
 Description : FileSystem for ReduceMapFast
 ============================================================================
 */

#include <unistd.h>
#include "thread_escuchas.h"
#include <cxdcommons/general.h>
#include "consola.h"
#include "opciones_consola.h"
#include "mongodb.h"

int estadoFS = 0;
int cantNodosMinimos;
t_list* listaNodos_limbo;
t_list* listaNodos_ok;

int printConsola(void);

int main(int argc, char **argv) {
	int iret;
	char opcion;
	t_config *config;
	pthread_t thread_escuchas;
	
	listaNodos_limbo = list_create();
	listaNodos_ok = list_create();

	config = readConfigurationFile(argv);
	cantNodosMinimos = config_get_int_value(config, "CANT_NODOS");

	iret = pthread_create(&thread_escuchas, NULL, (void *) &f_thread_escuchas, (void*) config);
	if( iret ){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
		exit(EXIT_FAILURE);
	}

	textoColor(VERDE); // cambia el color a verde
	limpiarPantalla();
	system("clear");

	for(;;){
		printConsola(); // imprime la consola
		opcion = getchar(); // obtiene la opcion deseada

		limpiarPantalla();
		if( opcion!='\n' ){
			switch( opcion ){
				default:
					printf("Opción incorrecta...\n");
					sleep(1);
					break;
				case '1':
					formatMDFS();
					break;
				case '2':
					//ABMArchive();
					break;
				case '3':
					//ABMDirectory();
					break;
				case '4':
					//copyFSLocalArchiveToMDFS();
					break;
				case '5':
					//copyMDFSArchiveToFSLocal();
					break;
				case '6':
					//archiveMD5();
					iniciar_mongo();
					sleep(3);
					break;
				case '7':
					//ABMArchiveBlocks();
					break;
				case '8':
					//addNode();
					break;
				case '9':
					//deleteNode();
					break;
				case 'q':
					goto FIN;
					break;
			}
		}
	}

	FIN:
		textoColor(NORMAL);
		limpiarPantalla();

		pthread_cancel( thread_escuchas );

		return EXIT_SUCCESS;
}

int printConsola(void) {
	limpiarPantalla();
	pTitulo("Consola de FileSystem");
	pWhiteLine();
	pOptionLine('1', "Formatear el MDFS.");
	pOptionLine('2', "Eliminar/Renombrar/Mover un archivo.");
	pOptionLine('3', "Crear/Eliminar/Renombrar/Mover un directorio.");
	pOptionLine('4', "Copiar un archivo LOCAL al MDFS.");
	pOptionLine('5', "Copiar un archivo del MDFS al FILESYSTEM LOCAL.");
	pOptionLine('6', "MD5 de un archivo.");
	pOptionLine('7', "Ver/Borrar/Copiar los bloques de un archivo.");
	pOptionLine('8', "Agregar un nodo de datos.");
	pOptionLine('9', "Eliminar un nodo de datos.");
	pOptionLine('q', "Cerrar programa.");
	pWhiteLine();
	pWhiteLine();
	pLineaDivisora();
	pText("Ingresar opción deseada: \033[s", 3);
	pFinConsola();
	printf("\033[u");
	return EXIT_SUCCESS;
}
