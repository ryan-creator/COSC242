#include <stdio.h>
#include <stdlib.h>

int score(double s1, double s2, double s3){
    if(s1 < s2 && s1 < s3){
        return (s2 + s3) / 2;
    }else if(s2 < s1 && s2 < s3){
        return (s1 + s3) / 2;
    }else{
        return (s1 + s2) / 2;
    }
}

int main(void){
    double s1, s2, s3, highest_score = 0.0;
    int highest_id = 0, id;

    while(4 == scanf("%d%lg%lg%lg", &id, &s1, &s2, &s3)){
        if(score(s1,s2,s3) > highest_score){
            highest_score = score(s1,s2,s3);
            highest_id = id;
        }
    }
    printf("\nThe ID of the winning competitor is: %d!\n", highest_id);
    
    return EXIT_SUCCESS;
}