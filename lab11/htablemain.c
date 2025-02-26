#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"

int main(void) {
	htable h = htable_new(18143);
	char word[256];

	while (getword(word, sizeof word, stdin) != EOF) {
		htable_insert(h, word);
	}

	htable_print(h, stdout);
	htable_free(h);
	
	return EXIT_SUCCESS;
}