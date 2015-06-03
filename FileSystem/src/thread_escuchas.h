/*
 * thread_escuchas.h
 *
 *  Created on: 3/6/2015
 *      Author: ezeyuske
 */

#ifndef SRC_THREAD_ESCUCHAS_H_
#define SRC_THREAD_ESCUCHAS_H_

	#include <pthread.h>
	#include <commons/config.h>
	#include <commons/collections/list.h>
	#include <commons/collections/dictionary.h>
	#include <cxdcommons/sockets.h>

	typedef struct {
		int fichero;
		char ip[16];
		char nodo_nuevo[3];
	} t_nodo;

	void f_thread_escuchas(void* param);

#endif /* SRC_THREAD_ESCUCHAS_H_ */
