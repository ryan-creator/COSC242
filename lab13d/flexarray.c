#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s){
    void *result = malloc(s);

    if(result == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(int *p, size_t s){
    void *result = realloc(p,s);

    if(result == NULL){
        fprintf(stderr, "Memory Reallocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

flexarray flexarray_new(){
    flexarray f = emalloc(sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(f->capacity * sizeof f->items[0]);

    return f;
}

void flexarray_append(flexarray f, int num){
    if(f->capacity == f->itemcount){
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = num;
    f->itemcount++;
}

void flexarray_print(flexarray f, FILE *stream){
    int i;

    for(i = 0; i < f->itemcount; i++){
        fprintf(stream, "%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    int i, j, key;

    for(i = 1; i < f->itemcount; i++){
        if(i == f->itemcount /2){
            flexarray_print(f, stderr);
        }
        key = f->items[i];
        j = i - 1;
        while(f->items[j] > key && j >= 0){
            f->items[j + 1] = f->items[j];
            j--;
        }
        f->items[j + 1] = key;
    }
}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}
