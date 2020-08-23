#include <stdio.h>
#include <stdlib.h>

int is_prime(int can) {
    int i = 0;
    
    for(i = 2; i < can; i++){
        if(can % i == 0){
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int can = 2;
    int num_printed = 0;

    while(num_printed < 100){
        if(is_prime(can)) {
            printf("%i ,",can);
            num_printed++;
        }
        can++;
    }
    return EXIT_SUCCESS;
}
