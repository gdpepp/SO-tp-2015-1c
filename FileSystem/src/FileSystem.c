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

int printConsola(void);

int main(void) {
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
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
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
		return EXIT_SUCCESS;
}

int printConsola(void){
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
