#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int getword(char *s, int limit, FILE *stream) {
int c;
char *w = s;
assert(limit > 0 && s != NULL && stream != NULL);
/* skip to the start of the word */
while (!isalnum(c = getc(stream)) && EOF != c)
;
if (EOF == c) {
return EOF;
} else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
*w++ = tolower(c);
}
while (--limit > 0) {
if (isalnum(c = getc(stream))) {
*w++ = tolower(c);
} else if ('\'' == c) {
limit++;
} else {
break;
}
}
*w = '\0';
return w - s;
}

void *emalloc(size_t s){
	void *result = malloc(s);
	if(result == NULL){
		fprintf(stderr, "Memory allocation error");
		exit(EXIT_FAILURE);
	}
	return result;
}

void *erealloc(void *p, size_t s){
	void *result = realloc(p,s);
	if(result == NULL){
		fprintf(stderr, "Memory allocation error");
		exit(EXIT_FAILURE);
	}
	return result;
}
