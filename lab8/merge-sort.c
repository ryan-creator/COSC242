#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10000

void merge(int *array, int *workspace, int length){
	int left = 0;
	int right = length / 2;
	int i;

	while(left < (length / 2) && right < length) {
		if(array[left] < array[right]){
			workspace[i] = array[left];
			left++;
		} else {
			workspace[i] = array[right]; 
			right++;
		} 
		i++;
	}

	while(left < (length / 2)) {
		workspace[i] = array[left];
		left++;
		i++;
	}

	while(right < (length / 2)) {
		workspace[i] = array[right];
		right++;
		i++;
	}
}

void merge_sort(int *array, int *workspace, int length){
	int i;

	if(length < 2){
		return;
	} else {
		merge_sort(array, workspace, (length / 2));
		merge_sort((array + (length / 2)), workspace, (length - (length / 2)));
	}

	merge(array, workspace, length);

	for(i = 0; i < length; i++){
		array[i] = workspace[i];
	}
}

int main(void){
	int workspace[ARRAY_MAX];
	int my_array[ARRAY_MAX];
	clock_t start, end;
	int i, count = 0;

	while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
		count++;
	}

	start = clock();
	merge_sort(my_array, workspace ,count);
	end = clock();

	for (i = 0; i < count; i++){
		printf("%d\n", my_array[i]);
	}

	fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}