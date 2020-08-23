#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* variable declarations */
    int i = 0;
    int f = 0;
    int g = 1;
    int temp = 0;
    
    for (i = 0; i < 40; i++) {
        printf("%i ,",g);
        temp = g;
        g = g + f;
        f = temp;
        if(i % 5 == 0 && i > 3){
            printf("\n");
        }
    }
    
    return EXIT_SUCCESS; /* defined in stdlib.h */
}
