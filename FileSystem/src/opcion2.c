/*

 * opcion2.c
 *
 *  Created on: Jun 6, 2015
 *      Author: gdpepp
 *     Program: ABM Archivos
 */


#include <stdio.h>
#include <stdlib.h>
#include "opciones_consola.h"
#include "consola.h"

 void opcion2 () {

 	char opcion;
 	char* ruta, nom_arch;
 	int fp;


 	opcion1:

 	pTitulo("ABM de Archivos");
	pWhiteLine();
	pOptionLine('1', "Crear un nuevo archivo");
	pOptionLine('2', "Renombrar un archivo");
	pOptionLine('3', "Mover un archivo");
	pOptionLine('q', "Salir del programa");

	opcion = getchar();

	switch (opcion) {

		case '1':
			printf ("Ingrese la ruta donde crear el nuevo archivo\n");
			scanf ("%s", &ruta);

			if (chdir (ruta) != 0)
				perror ("Error");

			printf ("Ingrese el nombre del archivo a crear: \n");
			scanf ("%s", nom_arch);
			if ((fp = fopen (ruta, "w")) != 0)
				perror ("ERROR");

			goto opcion1;
		case '2':




		default:
			printf("Opcion incorrecta \n");
			sleep (1);
			goto opcion1;
			break;


	}







 }
