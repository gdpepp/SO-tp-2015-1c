/*
 ============================================================================
 Name        : Job.c
 Author      : Esteban Raffo
 Version     : 0
 Copyright   : Your copyright notice
 Description : Proceso Job
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Pseudocodigo Elemental del Proceso Job");

/*
1)Leer archivo de configuración dado por el usuario (el usuario crea Job).

2)Se activa como Receptor de mensajes de Marta, establecer comunicación con Marta.

3)Se activa como Emisor de los nodos, establecer comunicación con los nodos.

4)Indicación a Marta de archivos existentes en el espacio temporal de los nodos.

5)Indicación a Marta sobre si soporta o no combiner.
  -Si el Job soporta combiner la planificación de las rutinas cambia.
  -Marta planifica rutinas para Job Con Soporte de Combiner.
  	   	   	   	   	   	   	        Sin Soporte de Combiner.


6)Indicación de Marta para iniciar hilo mapper e hilo reducer.

A- Si Marta indica Solicitud de mapping: "Aplicar rutina mapping sobre el Bloque 38 del Nodo X y almacenar el resultado en
  	  	  	  	  	  	  	  	  	  	 el archivo datosDeSalida.txt"
	1	-Crear instancia de Hilo Mapper

	2	-Solicitud de mapper: "Ejecutar mapper.sh sobre el Bloque 38 y almacenar el resultado en ArchivoDeSalida.txt"
		 El Hilo Mapper le pide al Nodo X aplicar rutina de mapping sobre el bloque solicitado y almacenar el resultado de forma ordenada en el
		 espacio temporal del Nodo X.

	3	-Generar conexion del Hilo Mapper con el Proceso Nodo X.
		-El Hilo Mapper envia al Nodo X: numero de bloque del espacio de datos + ejecutable + nombre archivo de salida

		4		En el proceso Nodo X (Interfaz con Hilo Mapper):
						Obtener datos del bloque solicitado al nodo y aplicar mapp:
									-Leer datos del bloque solicitado desde stdin.
									-Aplicar rutina de mapping, mapper.sh (convertir en formato deseable)
											-En caso de exito retorna 0
											-En caso de error retorna distinto de 0
									-Mostrar resultado por stdout.
									 (mapping genera registros parciales delimitados por \n).
									-Guardar en temporal.txt, (archivo de salida, espacio temporal dentro del nodo X).
									-Leer temporal.txt y Ordenar resultado de map por clave con programa sort.
									-Almacenar resultado en archivo de salida (espacio temporal dentro del nodo X).

		5		-Recibir respuesta del Proceso Nodo (el Nodo al Hilo).

		6	-El hilo mapper informa al Job resultado de la operacion sobre el bloque (el hilo al Job).

	7-Informar a Marta resultado de la operación de Job de Mapp sobre el bloque del Nodo X (el Job a Marta).
		  	-En caso de error Marta replanifica la operación en otro Nodo que contenga una copia del bloque.



B- Si Marta indica Solicitud de reduce: "Aplicar rutina de reduce en el Nodo X sobre datos3.txt (Nodo X), datos4.txt
									   (Nodo X) y datos11.txt (Nodo Y). Almacenar en total.txt"
	1	-Crear instancia de Hilo Reducer

	2	-Solicitud de reducer: Ejecutar reduce.sh sobre datos3.txt (Nodo X), datos4.txt (Nodo X) y datos11.txt (Nodo Y).
		 Almacenar en total.txt

	3	-Generar conexion a los Procesos Nodo X y Nodo Y.
		-El Hilo Reducer envia a los Nodos X e Y: nombre de archivos a reducir y sus Nodos + ejecutable + nombre archivo de salida.
		 Al menos un archivo es local al nodo, el resto puede ser de otros nodos.

	4	-Si Rutina Reduce recibe input de varios archivos (de otros Nodos por red)
				-Aplicar Algoritmo que aparea múltiples archivos de forma simultanea, eficiente y respetando distribución de carga del sistema.

	5	-Hilo Reducer les pide a los Nodos X e Y aplicar la rutina de reduce entre los archivos del espacio temporal.

				 En el/los Procesos Nodo X e Y (Interfaz con Hilo Reducer):
							-Leer contenido de archivos desde stdin (redireccionar).
							-Aplicar rutina de reduce, reduce.sh.
									-En caso de exito retorna 0
									-En caso de error retorna distinto de 0
							-Mostrar resultado por stdout.
							-Guardar salida stdout en total.txt (archivo de salida, espacio temporal).

		6		-Recibir respuesta del Proceso Nodo (el Nodo al Hilo).

		7	-El hilo reducer informa al Job resultado de la operación sobre los archivos (el hilo al Job).

	8-Informar a Marta resultado de la operacion del Job de reduce (el Job a Marta).
	  Ver Parametros de Configuracion para transmitir a Marta (Pag 9).
		  	-En caso de error Marta replanifica la operación de Mapping/Reduce en otro Nodo que contenga una copia del bloque.


7)Marta solicita a FS copiar el archivo de resultado al MDFS y avisa al Job el resultado de esa operacion.

8)Mostrar datos del proceso Job en pantalla y/o archivo de log (ver tabla pag 10).



*/

	return EXIT_SUCCESS;
}
