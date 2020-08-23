#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10000 // length of the array

/*
   Selection Sort class will receive an input of numbers.
   It will output the numbers sorted and the time it takes to sort the numbers.
   Author: Ryan Cole
 */

/*
  Selection sort will receive the first array items location and length.
  will sort the array.
 */
void selection_sort(int *a, int n){
    //variables to be used in the slection sort algorithm
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
    selection_sort(my_array, count);
    end = clock();

    //prints array
    for(i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
