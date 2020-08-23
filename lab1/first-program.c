#include <stdio.h>

int main(void) {
    int i;

    printf("Welcome to the C program.\n");
    printf("Let's print out some numberrs:\n");

    for(i = 0; i < 5; i++) {
          printf("%d\n",i);
    }

    printf("Finished.\n");
    return 100;
}
