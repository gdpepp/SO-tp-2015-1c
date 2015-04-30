/*
 ============================================================================
 Name        : fmmap.h
 Author      : Di Peppe, Gustavo Matias
 Version     : 1.0
 modified	 : 30/04/2015
 Description : definition of fmmap.h header
 ============================================================================
*/


#ifndef _fmmap_
#define _fmmap_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

char* mmapper(fileName);
void munmapper(char* mapeo, char* fileName);

#endif
