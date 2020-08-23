#ifndef MYLIB_H_
#define MYLIB_H_

#include <stdio.h>
#include <stddef.h>

/**
 * Author: Aidan Milne-Reeves, Ryan Cole and Jaraz Waerea.
 *
 * This header file contains the function declarations of mylib.c.
 */

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char*, int, FILE*);

#endif
