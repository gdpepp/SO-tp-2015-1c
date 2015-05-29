/*
 * Copyright (C) 2015 Grupo Compilo por Dinero. All rights reserved.
 */

#ifndef CXD_CONSOLA_H_
#define CXD_CONSOLA_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#define WIDTH_CONSOLE 120
	#define LATERAL "║"
	#define ESQUINA_SD "╗"
	#define ESQUINA_SI "╔"
	#define ESQUINA_ID "╝"
	#define ESQUINA_II "╚"
	#define LATERAL_CI "╠"
	#define LATERAL_CD "╣"
	#define LINEA_H "═"

	void limpiarPantalla(void);

	/**
	 * @NAME: textoColor
	 * @DESC: Cambia el color del texto
	 */
	void textoColor(int a);

	void pLineaDivisora(void);
	void pTitulo(char *titulo);
	void pWhiteLine(void);
	void pOptionLine(char option, char* label_option);
	void pText(char* texto, size_t add);
	void pFinConsola(void);

#endif
