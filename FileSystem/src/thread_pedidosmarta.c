/*
 * thread_pedidosmarta.c
 *
 *  Created on: 6/6/2015
 *      Author: ezeyuske
 */

#include "thread_escuchas.h"

void f_thread_pedidosmarta(void* param){
	//t_msjcxd* mensaje_send;
	//t_msjcxd* mensaje_recv;
	t_arg_pedidomarta* arg_hilo_marta;
	arg_hilo_marta = (t_arg_pedidomarta*) param;
	/* (codigo completo) */
}

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
