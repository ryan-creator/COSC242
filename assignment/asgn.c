#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "mylib.h"
#include "htable.h"
#include <time.h>

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}
/*
void search(htable h, char o, char *w) {
    while (2 == scanf(" %c %255s", &o, w)){
        if ('+' == o){
            htable_insert(h, w);
        } else if ('?' == o){
            printf("%d %s\n", htable_search(h, w), w);
        }
    }
}
*/

/* Function that check to see if i is a prime number or not */
int isPrime(int i){
    int j;
    for(j = 2; j < i; j++){
        if(i % j == 0){
            return 1;
        } 
    }
    return 0;
}

void print_help_message(void){
    printf("Usage: ./asgn [OPTION]... <STDIN>\n");

    printf("\n");

    printf("Perform various operations using a hash table. By default, words are\n"
           "read from stdin and added to the hash table, before being printed out\n"
           "alongside their frequencies to stdout.\n"
           );

    printf("\n");

    printf(" -c FILENAME  Check spelling of words in FILENAME using words\n"
           "              from stdin as dictionary.  Print unknown words to\n"
           "              stdout, timing info & count to stderr (ignore -p)\n"
           );

    printf(" -d           Use double hashing (linear probing is the default)\n");
    printf(" -e           Display entire contents of hash table on stderr\n");
    printf(" -p           Print stats info instead of frequencies & words\n");
    printf(" -s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
    printf(" -t TABLESIZE Use the first prime >= TABLESIZE as htable size\n");

    printf("\n");

    printf(" -h           Display this message\n");

    printf("\n");
}

int main(int argc, char **argv) {
    int tablesize = 113;
    char word[256];

    const char *opstring = "c:deps:t:h";
    char option;



    htable h = htable_new(tablesize, LINEAR_P);

    FILE *file;
    
    /*arg options*/
    int filename = 0;
    int doublehash = 0;
    int display_contents = 0;
    int print_stat = 0;
    int stats_snapshots = 0;
    int fp_tablesize = 0;
    int help_message = 0;
    int unknown_word_count;

    clock_t start_insert, end_insert, start_search, end_search, start_, fill_t, search_t;

    if(argc > 0) {
        while ((option = getopt(argc, argv, opstring)) != EOF) {
            switch(option) {
                case 'c':

                    file = fopen(optarg, "r");
                    
                    if(file == NULL) {
                        fprintf(stderr, "ERROR Could not open file %s\n", optarg);
                        exit(EXIT_FAILURE);
                    }

                    start_insert = clock();
                    
                    while(getword(word, sizeof word, file) != EOF) {
                        htable_insert(h, word);
                    }

                    end_insert = clock();
                     
                    fill_t = (double)(end_insert - (double)start_insert) / CLOCKS_PER_SEC;


                    
                    start_search = clock();     
                    
                     while(getword(word, sizeof word, stdin) != EOF) {
                         if(!htable_search(h,word)){
                             printf("%s\n", word);
                             unknown_word_count++;
                         }
                     }

                     end_search = clock();

                     search_t = (double)(end_search - (double)start_search) / CLOCKS_PER_SEC;

                     fclose(file);

                     fprintf(stderr, "Fill time     : %f\n"
                             "Search time   : %f\n"
                             "Unknown words = %d\n", fill_t, search_t, unknown_word_count
                             );
                     
               
                    break;
                case 'd':
                    /*double hashing instead of linear probbing.
                      Linear is default.*/
                    doublehash = 1;
                    break;
                case 'e':
                    /*Display all hash contents on stderr
                      index, freq, stats and key if it exists*/
                    display_contents = 1;
                    break;
                case 'p':

                    break;
                case 's':

                    break;
                case 't':
      
                    break;
                case 'h':
                    /*Print a help message describing how to use. default
                      should be the same*/
                    print_help_message();
                    break;
                default :
                    print_help_message();
                    exit(EXIT_FAILURE);
                    /*Help*/
            }
        }
    }
    if(filename == 1) {
        /*
        printf("filename test\n");
        while (2 == scanf(" %c %255s", &op, word)) {
            if('+' == op) {
                htable_insert(h, word);
            } else if('?' == op) {
                printf("%d %s\n", htable_search(h, word), word);
            }
        }
        */

        /*
          Get the words from the first file and insert them into them
          the htable to create the dictionairy. 
        */

        
        

        
    }
    if(doublehash == 1) {
        printf("doublehash test\n");
    }
    if(display_contents == 1) {
        printf("dispaly_contents test\n");
    }
    if(print_stat == 1) {
        printf("print_stat test\n");
    }
    if(stats_snapshots == 1) {
        printf("stats_snapshots test\n");
    }
    if(fp_tablesize == 1) {   
    }
    if(help_message == 1) {
        printf("help_message test\n");
    }
    
    htable_free(h);

    return EXIT_SUCCESS;
}
