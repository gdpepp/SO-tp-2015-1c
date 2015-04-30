/*
 ============================================================================
 Name        : fmmap.c
 Author      : Di Peppe, Gustavo Matias
 Version     : 2.0
 modified	 : 30/04/2015
 Description : definition of functions for fmmap.h
 ============================================================================
*/

#include "fmmap.h"

//	private functions

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
	int fd = getFileDescriptor(fileName);
	int size = getFileSize(fd);

	if( (mapeo = mmap( NULL, size, PROT_READ, MAP_SHARED, fd, 0 )) == MAP_FAILED){
		//if MMAP could not be executed, print error and abort
		fprintf(stderr, "Error executing MMAP file '%s' of size: %d: %s\n", fileName, size, strerror(errno));
		abort();
	}
	return mapeo;
}

void munmapper(char* mapeo, char* fileName) {
	int fd = getFileDescriptor(fileName);
	int size = getFileSize(fd);

	//unmap and close
	if(munmap(mapeo,size) == -1)
		fprintf(stderr, "error executing MUNMAP file '%s' of size %d: %s\n", fileName, size, strerror(errno));
	if(close(fd) == -1)
		fprintf(stderr, "Error closing file '%s': %s\n", fileName, strerror(errno));
}
