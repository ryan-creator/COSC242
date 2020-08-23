#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include <stdlib.h>
struct htablerec {
int capacity;
int num_keys;
char **keys;
};
static unsigned int htable_word_to_int(char *word) {
unsigned int result = 0;
while (*word != '\0') {
result = (*word++ + 31 * result);
}
return result;
}

htable htable_new(int capacity) { 
	int i;

	htable h = emalloc(sizeof *h);

	h -> capacity = capacity;
	h -> num_keys = 0;
	h -> keys = emalloc(h -> capacity * sizeof h -> keys[0]);

	for(i = 0; i < h -> capacity; i++){
		h -> keys[i] = NULL;
	}
	return h;
}

void htable_free(htable h) {
	int i;
	for(i = 0; i < h -> capacity; i++){
		free(h -> keys[i]);
	}

	free(h -> keys);
	free(h);
}

int htable_insert(htable h, char *key) {
	int attempts = 0;
	unsigned int index = htable_word_to_int(key);
	index = index % h -> capacity;

	while(1){
		if(h -> keys[index] == NULL){
			h -> keys[index] = erealloc(h -> keys[index], strlen(key) + 1 * sizeof key[0]);
			strcpy(h -> keys[index], key);
			h -> num_keys++;
			return 1;
		} else {
			if(strcmp(h -> keys[index], key) == 0){
				return 1;
			}	
		}
		if(attempts == h -> capacity){
			return 0;
		}
		attempts++;
		index = (index + 1) % h -> capacity;
	}
}

void htable_print(htable h, FILE *stream) { 
	int i;
	for (i = 0; i < h->capacity; i++) {
fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
}

}