/*
 ============================================================================
 Name        : FileSystem.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : FileSystem for ReduceMapFast
 ============================================================================
 */

#include "consola.h"

int main(void) {
	system("clear");
	textoVerde(1);
	while(1){
		system("clear");
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
		if( getchar()=='q' ) break;
	}
	textoVerde(0);
	system("clear");
	return EXIT_SUCCESS;
}
