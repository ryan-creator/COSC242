#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10000

void selection_sort(int *a, int n){
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

int main(int argc, char **argv) {
    FILE *infile, *infile2;
    int my_array[ARRAY_SIZE];
    int num_items;
    int i, input;
    int check = 0;
    
    if (NULL == (infile = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s: can’t find file %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }
    
    num_items = 0;
    while (num_items < ARRAY_SIZE &&
           1 == fscanf(infile, "%d", &my_array[num_items])) {
        num_items++;
    }

    selection_sort(my_array, num_items);

    fclose(infile);

    if(NULL == (infile2 = fopen(argv[2], "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[2]);
        return EXIT_FAILURE;
    }

    while (1 == fscanf(infile2, "%d", &input)){
        for(i = 0; i < num_items; i++){
            if(input == my_array[i]){
                printf("%d : +\n", my_array[i]);
                check = 1;
            }
        }
        if(check == 0){
            printf("-\n");
        }
        check = 0;
    }
    
    return EXIT_SUCCESS;
}


