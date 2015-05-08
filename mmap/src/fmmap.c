/*
 =============================================================================
 Name        : fmmap.c
 Author      : Di Peppe, Gustavo Matias
 Version     : 2.1
 modified	 : 30/04/2015
 Description : definition of functions for fmmap.h
 =============================================================================

 =============================================================================
 contrato:	 : MUNMAP se realiza en LIFO (sobre ultimo archivo en stack)
 =============================================================================
*/

#include "fmmap.h"

// file properties struct
typedef struct fileProperties {
	int fd;
	int size;
} t_fileprops;

//	stack struct
struct node{
	t_fileprops value;
	struct node *next;
};

static struct node *top=0;


//	private functions

static void push(t_fileprops v) {
	struct node *p;
	if(( p = malloc(sizeof *p) ) == NULL ){
		perror("No memory left");
		exit(EXIT_FAILURE);
	}
	p->next = top;
	top = p;
	p->value = v;
}

static t_fileprops pop(void) {
	t_fileprops value = top->value;
	struct node *p = top;

	top = top->next;
	free(p);

	return value;
}

static int getFileSize(const int filedescriptor) {
	struct stat buffer;
	fstat(filedescriptor, &buffer);
	return buffer.st_size;
}

static int getFileDescriptor(char* fileName) {
	int fd;
	if((fd = open(fileName, O_RDONLY)) == -1) {
		//if error, print it and abort
		fprintf(stderr, "Error opening file '%s': %s\n", fileName, strerror(errno));
		abort();
	}
	return fd;
}

// 	public functions

char* mmapper(fileName){
	char* mapeo;
	t_fileprops fileprops;
	fileprops.fd = getFileDescriptor(fileName);
	fileprops.size = getFileSize(fileprops.fd);

	if( (mapeo = mmap( NULL, fileprops.size, PROT_READ, MAP_SHARED, fileprops.fd, 0 )) == MAP_FAILED){
		//if MMAP could not be executed, print error and abort
		fprintf(stderr, "Error executing MMAP file '%s' of size: %d: %s\n", fileName, fileprops.size, strerror(errno));
		abort();
	}

	push(fileprops);
	return mapeo;
}

void munmapper(char* mapeo) {

	t_fileprops fileprop = pop();

	//unmap and close
	if(munmap(mapeo,fileprop.size) == -1)
		fprintf(stderr, "error executing MUNMAP for file of size %d: %s\n", fileprop.size, strerror(errno));
	if(close(fileprop.fd) == -1)
		fprintf(stderr, "Error closing file: %s\n", strerror(errno));
}
