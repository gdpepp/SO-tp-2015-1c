/*
 ============================================================================
 Name        : RedireccionarStdinStdout.c
 Author      : Esteban Raffo
 Version     : 0
 Copyright   : Your copyright notice
 Description : Se usaron archivos de E/S .txt de ejemplo, pero para los fines del tp también se aplicarán los
 	 	 	   script de map y reduce. Al leer un bloque se requiere redireccionarlo desde teclado o archivo.txt a
 	 	 	   mapper.sh y luego leer desde archivo.txt y redireccionarlo a reduce.sh (pags 16-18 del enunciado).

			   Pendiente a resolver:
			   -¿Cómo implementar un bloque de 20 MB en C?
			   -¿Se deben desarrollar los .c para enviar como interprete a los script mapper y reduce (ver "Sobre
			     los scripts y sus interpretes")?
 ============================================================================

Ejecución desde comando:

Para redireccionar solo stdin:
$ ./redireccionar < archDeEntrada.txt (lee bloques desde archDeEntrada.txt y los muestra en pantalla)

Para redireccionar stdin y stdout:
$ ./redireccionar < archDeEntrada.txt > archDeSalida.txt (lee bloques desde archDeEntrada.txt y los guarda en
															archDeSalida.txt)
*/

#include <stdio.h>


typedef struct{
	char nombre[21];
	char apellido[21];
	unsigned edad;
}registro;            //Se toma un registro basico como bloque. Ver como implementar registro de 20 MB.


int main(void) {

	unsigned i;
	registro persona[5];

	printf("Ingrese nombre, apellido y edad\n\n");
	for(i = 0; i < 5; i++){
		fscanf(stdin, "%s", persona[i].nombre);
		fscanf(stdin, "%s", persona[i].apellido);
		fscanf(stdin, "%u", &persona[i].edad);
		fprintf(stdout,"Nombre: %s\nApellido: %s\nEdad: %u\n\n", persona[i].nombre, persona[i].apellido, persona[i].edad);
	}
	return 0;
}
