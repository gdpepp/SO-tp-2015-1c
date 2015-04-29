#include "consola.h"

void limpiarPantalla(void){
	printf("\n"); // corrige BUG al limpiar la consola
	system("clear");
}
void textoColor(int a){
	const char *const verde = "\033[1;0;32m";
	const char *const normal = "\033[0m";
	if( a )
		printf("%s", verde);
	else
		printf("%s", normal);
}
void pLineaDivisora(void){
	int i;
	printf("%s", LATERAL_CI);
	for(i=0; i<WIDTH_CONSOLE; i++)
		printf("%s", LINEA_H);
	printf("%s\n", LATERAL_CD);
}
void pTitulo(char *titulo){
	div_t padding;
	size_t i, len;
	len = strlen(titulo);
	printf("%s", ESQUINA_SI);
	for(i=0; i<WIDTH_CONSOLE; i++)
		printf("%s", LINEA_H);
	printf("%s\n", ESQUINA_SD);
	printf("%s", LATERAL);
	padding = div((WIDTH_CONSOLE - len), 2); // hace la divicion y guarda el entero y el resto en un tipo de estructura
	for(i=0; i<padding.quot; i++)
		printf(" ");
	printf("%s", titulo);
	for(i=0; i<padding.quot; i++)
		printf(" ");
	if( padding.rem==1 ) printf(" ");
	printf("%s\n", LATERAL);
	pLineaDivisora();
}
void pWhiteLine(void){
	int i;
	printf("%s", LATERAL);
	for(i=0; i<WIDTH_CONSOLE; i++)
		printf(" ");
	printf("%s\n", LATERAL);
}
void pOptionLine(char option, char* label_option){
	int i, padding_right;
	printf("%s [%c] %s", LATERAL, option, label_option);
	padding_right = WIDTH_CONSOLE - 5 - strlen(label_option);
	for(i=0; i<padding_right; i++)
		printf(" ");
	printf("%s\n", LATERAL);
}
void pText(char* texto, size_t add){
	size_t i, len, padding;
	len = strlen(texto);
	padding = WIDTH_CONSOLE + add - len;
	printf("%s %s", LATERAL, texto);
	for(i=0; i<padding; i++)
		printf(" ");
	printf("%s\n", LATERAL);
}
void pFinConsola(void){
	int i;
	printf("%s", ESQUINA_II);
	for(i=0; i<WIDTH_CONSOLE; i++)
		printf("%s", LINEA_H);
	printf("%s\n", ESQUINA_ID);
}
