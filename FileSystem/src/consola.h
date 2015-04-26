#ifndef _fconsola_
#define _fconsola_

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

void textoVerde(int a);
void pLineaDivisora(void);
void pTitulo(char *titulo);
void pWhiteLine(void);
void pOptionLine(char option, char* label_option);
void pText(char* texto, size_t add);
void pFinConsola(void);

#endif
