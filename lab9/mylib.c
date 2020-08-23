#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */

#include "mylib.h"

void *emalloc(size_t s) {
	void *result = malloc(s);

	if(result == NULL){
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	return result;
}

void *erealloc(void *p, size_t s) {
	void *result = realloc(p, s);

	if(result == NULL){
		fprintf(stderr, "memory Reallocation failed.\n");
		exit(EXIT_FAILURE);
	}

	return result;
}