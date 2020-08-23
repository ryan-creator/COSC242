#include <stdlib.h>
#include <stdio.h>
#include "mylib.c"
#include "htable.h";

struct htablerec {
	int num_keys;
	int* frequencies;
	int capacity;
	int** keys;
};

void htable_print(htable h, FILE *stream){
	int i;

	for(i = 0; i < h -> capacity; i++){
		if(h -> keys[i] != NULL){
			fprintf(stream, "Frequency: %05d: %s\n", h -> frequencies[i], h -> keys[i]);
		}
	}
}

static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_search(htable h, char *str){
    unsigned int index = htable_word_to_int(str);
}

static unsigned int htable_step(htable h, unsigned int i_key){
	int attempts = 0;
	unsigned int index = htable_word_to_int(str);
	unsigned int step;

	step = htable_step(h, index);

	while(h -> keys[index] != NULL && strcmp(h -> keys[index], str != 0) && attemmpts != h -> capacity) {
		index = index + step;
		attempts++;
	}

	if(attempts == h -> capacity){
		return 0;
	} else {
		return h -> frequencies[index];
	}
}

int htable_insert(htable h, char *str) {
	int attempts = 0;
	unsigned int index = htable_word_to_int(str);
	unsigned int step;

	index = index % h -> capacity;
	while(1){
		if(h -> keys[index] == NULL){
			h -> keys[index] erealloc(h -> keys[index], strlen(str) + 1 * sizeof str[0]);
			strcpy((h -> keys[index]), str);
			h -> frequencies[index] = 1;
			h -> num_keys++;
			return 1;
		} else if(strcmp(h -> keys[index], str) == 0){
			h -> frequencies[index]++;
			return h -> frequencies[index];
		} else {
			if(attempts == h -> capacity){
				return 0;
			}
			index = (index + step) % h -> capacity;
			attempts++; 
		}
	}
}

void htable_free(htable h) {
	int i;
	for(i = 0; i < h -> num_keys; i++){
		free(h -> keys[i]);
	}
	free(h -> keys);
	free(h -> frequencies);
	free(h);
}

htable htable_new(int capacity){
	int i;

	htable result = emalloc(sizeof *result);
	result -> capacity = 11;
	result -> num_keys = 0;
	result -> frequencies = emalloc(result -> capacity * sizeof result -> frequencies[0]);
	result -> keys = emalloc(result -> capacity * sizeof result -> keys[0]);

	for(i = 0; i < capacity; i++){
		result -> keys[i] = NULL;
		result -> frequencies[i] = 0; 
	}

	return result;	
}
