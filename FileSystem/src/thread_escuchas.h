/*
 * thread_escuchas.h
 *
 *  Created on: 3/6/2015
 *      Author: ezeyuske
 */

#ifndef SRC_THREAD_ESCUCHAS_H_
#define SRC_THREAD_ESCUCHAS_H_

	#include <stdbool.h>
	#include <pthread.h>
	#include <commons/config.h>
	#include <commons/collections/list.h>
	#include <commons/collections/dictionary.h>
	#include <cxdcommons/sockets.h>

	typedef struct {
		int fichero;
		char ip[16];
		char nodo_nuevo[3];
		char nombre[12];
	} t_nodo_fs;

	typedef struct {
		int fd_marta;
		t_msjcxd* mensaje_recv;
	} t_arg_pedidomarta;


	void f_thread_escuchas(void* param);
	void f_thread_pedidosmarta(void* param);
	
	t_link_element* list_find_element(t_list *self, bool(*condition)(void*, void*), int* index, void* argumento);

#endif /* SRC_THREAD_ESCUCHAS_H_ */
