/*
 ============================================================================
 Name        : mmap.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>



int fileSize(const int filedescriptor)
{
	struct stat buffer;
	fstat(filedescriptor, &buffer);
	return buffer.st_size;
}

int main(void)
{
	char* fileName = "test.dat";
	int fd;
	char* mapeo;
	int size;

	if(( fd = open(fileName, O_RDONLY) ) == -1) {
		//if error, print it and abort
		fprintf(stderr, "Error opening file '%s': %s\n", fileName, strerror(errno));
		abort();
	}
	size = fileSize(fd);
	if( (mapeo = mmap( NULL, size, PROT_READ, MAP_SHARED, fd, 0 )) == MAP_FAILED){
		//if MMAP could not be executed, print error and abort
		fprintf(stderr, "Error executing MMAP file '%s' of size: %d: %s\n", fileName, size, strerror(errno));
		abort();
	}

	printf ("Size of file: %d\nContent:'%s'\n", size, mapeo);

	//unmap and close
	if(munmap(mapeo,size) == -1)
		fprintf(stderr, "error executing MUNMAP file '%s' of size %d: %s\n", fileName, size, strerror(errno));
	if(close(fd) == -1)
		fprintf(stderr, "Error closing file '%s': %s\n", fileName, strerror(errno));

	return EXIT_SUCCESS;
}
