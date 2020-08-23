#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000 // length of the array

/*
  Insertion Sort class will receive an input of numbers.
  It will output the numbers sorted and the time it takes to sort the numbers.
  Author: Ryan Cole
*/

/*
  Insertion sort will receive the first array items location and length.
  will sort the array.
*/

void insertion_sort(int *a, int n){
    //variables to be used in the insertion sort algorithm
    int i, key, j = 0;
    
    for(i = 1; i < n; i++){
        key = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j = j -1;
        }
        a[j+1] = key;
    }
}

/*
  Creates the array, calls the sort algorithm
  records the time takes to sort the array
  prints out the sorted array and time taken to sort.
*/
int main(void) {
    int my_array[ARRAY_MAX];
    int i, count = 0;
    clock_t start, end;

    // reads in the numbers into the array
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    start = clock(); 
    insertion_sort(my_array, count);
    end = clock();

    //prints array
    for(i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
