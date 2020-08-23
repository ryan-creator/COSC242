#include <stdio.h>
#include <stdlib.h>

int is_prime(int c){
	int i;

	for(i = 2; i < c; i++){
		if(c % i == 0){
			return 0;
		}
	}
	return 1;
}

int main(void){
	int p = 0;
	int c = 2;

	while(p < 200){
		if(is_prime(c)){
			printf("%5d", c);
			p++;
			if(p % 10 == 0){
				printf("\n");
			}
		}
		c++;
	}	
	return EXIT_SUCCESS;
}