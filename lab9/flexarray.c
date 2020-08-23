#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"


static void array_print(int *a, int n){
	int i;

	for(i = 0; i < n; i++){
		printf("%d\n", a[i]);
	}
}

void array_sort(int *a, int n){
    int smallestIndex, i, j, value, temp = 0;

    for(i = 0; i < n; i++){
        smallestIndex = i;
        value = a[i];
        for(j = i; j < n; j++){
            if(a[j] < value){
                value = a[j];
                smallestIndex = j;
            }
        }
        temp = a[i];
        a[i] = a[smallestIndex];
        a[smallestIndex] = temp;
        
    }
    
}

int main(void) {
	int capacity = 2;
	int itemcount = 0;
	int item;
	int *my_array = emalloc(capacity * sizeof my_array[0]);

	while(1 == scanf("%d", &item)) {
		if(itemcount == capacity){
			capacity += capacity;
			my_array = erealloc(my_array, capacity * sizeof my_array[0]);		
		}	
		my_array[itemcount++] = item;
	}

	array_sort(my_array, itemcount);
	array_print(my_array, itemcount);
	free(my_array);

	return EXIT_SUCCESS;
}