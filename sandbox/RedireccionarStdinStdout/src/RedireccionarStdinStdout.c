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

El Nodo va a tener que ejecutar algo equivalente a ./mapper < BloqueDeDatos > ArchivoTemporal

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


/* Fuente: https://jineshkj.wordpress.com/2006/12/22/how-to-capture-stdin-stdout-and-stderr-of-child-program/

#include <unistd.h>
#include <stdio.h>

/* since pipes are unidirectional, we need two pipes.
   one for data to flow from parent's stdout to child's
   stdin and the other for child's stdout to flow to
   parent's stdin */

/*
#define NUM_PIPES          2

#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1

int pipes[NUM_PIPES][2];

/* always in a pipe[], pipe[0] is for read and
   pipe[1] is for write */
/*
#define READ_FD  0
#define WRITE_FD 1

#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )

#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

void main()
{
    int outfd[2];
    int infd[2];

    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);

    if(!fork()) {
        char *argv[]={ "/usr/bin/bc", "-q", 0};

        dup2(CHILD_READ_FD, STDIN_FILENO);
        dup2(CHILD_WRITE_FD, STDOUT_FILENO);

        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
/*      close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);

        execv(argv[0], argv);
    } else {
        char buffer[100];
        int count;

        /* close fds not required by parent */
/*      close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);

        // Write to child’s stdin
        write(PARENT_WRITE_FD, "2^32\n", 5);

        // Read from child’s stdout
        count = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);
        if (count >= 0) {
            buffer[count] = 0;
            printf("%s", buffer);
        } else {
            printf("IO Error\n");
        }
    }
}
 */




