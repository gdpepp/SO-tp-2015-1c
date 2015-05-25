/*
 ============================================================================
 Name        : FileSystem.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : FileSystem for ReduceMapFast
 ============================================================================
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "consola.h"
#include <commons/string.h>
#include <commons/config.h>
#include <cxdcommons/general.h>
#include <cxdcommons/sockets.h>
//#include <bson.h>
//#include <mongoc.h>


int printConsola(void);

int main(int argc, char **argv) {
	char opcion;
	textoColor(1); // cambia el color a verde
	limpiarPantalla();
	system("clear");

	CONSOLA:
		printConsola(); // imprime la consola
		opcion = getchar(); // obtiene la opcion deseada

		limpiarPantalla();
		if( opcion!='\n' ){
			switch( opcion ){
				default:
					printf("Opción incorrecta...\n");
					sleep(1);
					goto CONSOLA;
					break;
				case '1':
					//formatMDFS();
					//break;
				case '2':
					//ABMArchive();
					//break;
				case '3':
					//ABMDirectory();
					//break;
				case '4':
					//copyFSLocalArchiveToMDFS();
					//break;
				case '5':
					//copyMDFSArchiveToFSLocal();
					//break;
				case '6':
					//archiveMD5();
					//break;
				case '7':
					//ABMArchiveBlocks();
					//break;
				case '8':
					//addNode(); ?????  el nodo se conecta al fs
					//break;
				case '9':
					//deleteNode(); ??? el nodo se conecta al fs
					printf("Opcion %c.\nEspera 3seg para continuar...\n", opcion);
					sleep(3);
					limpiarPantalla();
					goto CONSOLA;
					break;
				case 'q':
					goto FIN;
					break;
			}
		}else{
			goto CONSOLA;
		}

	FIN:
		textoColor(0);
		limpiarPantalla();

	readConfigurationFile(argc, **argv);




		return EXIT_SUCCESS;
}

int printConsola(void) {
	pTitulo("Bienvenid@ a la consola de FileSystem");
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


void formatMDFS() {
	pWhiteLine();
	pTitulo("¿Seguro que desea borrar el MDFS?");
	pOptionLine('y', "Borrar MDFS (no puede deshacerse)");
	pOptionLine('n', "Cerrar programa.");
	pWhiteLine();
	pWhiteLine();
	pLineaDivisora();
	pText("Ingresar opción deseada: \033[s", 3);
	pFinConsola();
}


readConfigurationFile(int argc, char **argv) {
	char* config_path = string_new();
	string_append(&config_path, getAppPath(argv[0]));
	string_append(&config_path, "/config.cfg");
	t_config *config;
	char* puerto_fs;
	int cantNodos_fs;

	if( access( config_path, F_OK ) == -1 ){
		perror("config_path"); // Error de acceso al archivo
		exit(1);
	}

	config = config_create(config_path);
	free(config_path);
	puerto_fs = config_get_string_value(config, "PUERTO_FS");
	cantNodos_fs = config_get_int_value(config, "CANTNODOS_FS");

	printf("El puerto de FS es: %s\n", puerto_fs);
	printf("La cantidad de nodos es: %d\n", cantNodos_fs);

	config_destroy(config);
	return EXIT_SUCCESS;

}


//___________________________hasta aca parte consola___________________________

/*
SendNodesBlocksByArchiveName(char *archiveName){

	init struct nodosAEnviar
		// struct key-value de diccionario de nodos (nodo i, status nodo i)
		// status archivo (0 completo, 1 incompleto, -1 error)

	buscar en el FS el archivo
	recorrer diccionario nodos
		if (archiveExistsIn(Node))
			addNode(nodoi, nodosAEnviar)

	verifyArchiveStatus(nodosAEnviar)
	//verifica si con los nodos que se encuentra en el struct el archivo esta completo.

	generar mensaje t_msjcxd mensaje con struct nodosAEnviar
	serializar t_msjcxd

	send(mensaje serializado)
}
*/
