#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayec {
	int capacity;
	int itemcount;
	int *items
}

flexarray flexarray_new() {
	flexarray result = emalloc(sizeof *result);
	result -> capacity = 2;
	result -> itemcount = 0;
	result -> items = emalloc(result -> capacity * sizeof result -> items[0]);
	return result;
}

void flexarray_append(flexarray f, int num){
	if(f -> itemcount == f -> capacity) {
		f -> capacity += f -> capacity;
		f -> items = erealloc(f -> items, f -> capacity * sizeof f -> items[0] );
	}
	f -> items[f -> itemcount++] = num;
}

void flexarray_print(flexarray f) {
	int i;

	for(i = 0; i < f -> itemcount; i++){
		printf("%d\n", f -> item[i]);
	}
}

void flexarray_sort(flexarray f){
    int i, smallestIndex, value, j, temp;
    int n = f -> itemcount;

    for(i = 0; i < n; i++){
        smallestIndex = i;
        value = f -> items[i];
        for(j = i; j < n; j++){
            if(f -> items[j] < value){
                value = f -> items[j];
                smallestIndex = j;
            }
        }
        temp = f -> items[i];
        f -> items[i] = f -> items[smallestIndex];
        f -> items[smallestIndex] = temp;
        
    }
}

void flexarray_free(flexarray f){
	free f
}