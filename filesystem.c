/*
 * main.c
 *
 *  Created on: 25/4/2015
 *      Author: utnso
 *      Objetivo: Mock del menu del Filesystem
 */

#include <stdio.h>
#include <stdlib.h>

#define OP1 '1'

int main () {

	char op;

	printf ("Bienvenido al Filesystem de Marta\n\n");
	printf ("[1] Formatear MDFS\n");
	printf ("[2] Crear/Eliminar/Renombrar/Mover directorios\n");
	printf ("[3] Copiar un archivo local al MDFS\n");
	printf ("[4] Copiar un arcihvo del MDFS al filesystem local\n");
	printf ("[5] Solicitar el MD5 de un archivo en MDFS\n");
	printf ("[6] Ver/Borrar/Copiar los bloques que componen un archivo\n");
	printf ("[7] Agregar un nodo de datos\n");
	printf ("[8] Eliminar un nodo de datos\n\n");

	printf ("Por favor, ingrese la opcion deseada:");
	op = getchar();

	switch (op) {
		case OP1 :
			printf ("Opcion 1\n");
			break;
		case '2':
			printf ("Opcion 2\n");
			break;
		case '3':
			printf ("Opcion 1\n");
			break;
		case '4':
			printf ("Opcion 1\n");
			break;
		case '5':
			printf ("Opcion 1\n");
			break;
		case '6':
			printf ("Opcion 1\n");
			break;
		case '7':
			printf ("Opcion 1\n");
			break;
		case '8':
			printf ("Opcion 1\n");
			break;
		default: printf ("La opcion ingresada es incorrecta\n");

	}

	return EXIT_SUCCESS;




}
