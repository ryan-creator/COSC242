#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LEN 80

void *emalloc(size_t s){
	void *result = malloc(s);
	if(result == NULL){
		fprintf(stderr, "Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

void print_array(char **words_array, double average_len, int count){
	if(count > 0){
		if(strlen(words_array[0]) > average_len) {
			printf("%s\n", words_array[0]);
		}
		print_array(words_array + 1, average_len, count - 1);
	}
}

int main(void) {

	char word[MAX_LEN];
	char *words_array[MAX_WORDS];

	int i, count = 0;
	double average_len = 0.0;

	while(count < MAX_WORDS && 1 == scanf("%79s", word)) {
		words_array[count] = emalloc((strlen(word) + 1) * sizeof words_array[0]);
		strcpy(words_array[count], word);
		average_len += strlen(word);
		count++;
	}

	if(count > 0){
		average_len /= count;
		fprintf(stderr, "%.2f\n", average_len);
		print_array(words_array, average_len, count);
	}

	for(i = 0; i < count; i++){
		free(words_array[i]);
	}

	return EXIT_SUCCESS;

}