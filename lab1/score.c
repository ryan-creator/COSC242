#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int reg_number = 0;
    int winner = 0;
    double s1 = 0.0;
    double s2 = 0.0;
    double s3 = 0.0;
    double highest_score = 0.0;

    while(1 == scanf("%d%lg%lg%lg", &reg_number, &s1, &s2, &s3)){
        if(s1 + s2 + s3 > highest_score){
            highest_score = s1 + s2 + s3;
            winner = reg_number;
        }
    }

    printf("Winning Score: %f \nWinner: %i \n", highest_score, winner);
    
    return EXIT_SUCCESS;
}
