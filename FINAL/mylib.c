#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Author: Aidan Milne-Reeves, Ryan Cole and Jaraz Waerea  
 *
 * The purpose of this class is to hold helper functions like allocating and
 * reallocating memory for the program. As well as the getword() funtion.
 */

/**
 * Attempt to allocate memory using malloc(); return the memory address
 * on success; print an error message on stderr and then terminate the
 * program on failure.
 *
 * @param s the size of the memory to be allocated
 * @return result will return the memory address on success
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Mem allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Attempt to allocate memory using realloc(); return the memory address
 * on success; print an error message on stderr and then terminate the
 * program on failure.
 *
 * @param p the pointer that you want to reallocate
 * @param s the size of the memory to be allocated
 * @return result returns a (possibly different) pointer whose contents up to
 *         the minimum of the old and new sizes are unchanged
 */
void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if(NULL == result) {
        fprintf(stderr, "Mem reallocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Reads words from stdin.
 *
 * @param s the pointer to the first character
 * @param limit the word limit size
 * @param stream the stream to send output to
 * @return the word you wish to recieve
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    /* skip to the start of the word */
    while(!isalnum(c = getc(stream)) && EOF != c)
        ;
    if(EOF == c) {
        return EOF;
    } else if(--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while(--limit > 0) {
        if(isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
