#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

/**
 * Author: Aidan Milne-Reeves, Ryan Cole and Jaraz Waerea  
 *
 * The purpose of this program is to compare different hashing strategies. This
 * is accomplished by performing both linear or double hashing, and printing
 * the results in various ways to best understand the differences.
 *
 * This file contains the main method and the command line arguments options
 * used to perform the tasks needed.
 */

/**
 * Checks in the file stream has input or not, if there is input nothing
 * happens, if there is no input it will exit the program.
 *
 * @param *input is the input stream of type FILE
 */
void file_failure_check(FILE *input){
    if(input == NULL) {
        fprintf(stderr, "ERROR Could not open file %s\n", input);
        exit(EXIT_FAILURE);
    }
}

/**
 * Check the spelling of words in filename using words
 * fromstdin as the dictionary. Print all unknown words
 * stdout. Print timing information and unknown word to stderr.
 * 
 * @param h is the htable which contains the dictionairy words.
 */
void compare_files(htable h){

    FILE *file;
    int unknown_word_count = 0;
    char word[256];
    clock_t start_insert, end_insert, start_search, end_search;
    long double fill_t, search_t; 

    file = fopen(optarg, "r");
        
    file_failure_check(file);

    start_insert = clock();
    
    while(getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }

    end_insert = clock();

    fill_t = (double)(end_insert - (double)start_insert) / CLOCKS_PER_SEC;

    start_search = clock();     
    
    while(getword(word, sizeof word, file) != EOF) {
        if(!htable_search(h,word)){
            printf("%s\n", word);
            unknown_word_count++;
        }
    }
    
    end_search = clock();

    search_t = (double)(end_search - (double)start_search) / CLOCKS_PER_SEC;

    fclose(file);

    fprintf(stderr, "Fill time     : %Lf\n"
            "Search time   : %Lf\n"
            "Unknown words = %d\n", fill_t, search_t, unknown_word_count
            );
}

/**
 * This method checks if the inserted int is a prime number.
 *
 * @param i an int to be check if it is a prime number
 */
int isPrime(int i) {
    int j;
    for(j = 2; j < i; j++) {
        if(i % j == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * This method prints out all the options and their functions for using the
 * program.
 */
void print_help_message(){
    printf("Usage: ./asgn [OPTION]... <STDIN>\n");

    printf("\n");

    printf("Perform various operations using a hash table. By default, "
           "words are\n"
           "read from stdin and added to the hash table, before being "
           "printed out\n"
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
    
    exit(EXIT_FAILURE);
}

/**
 * The main method of the program. Contains the code for the argument selection
 * that the user enters and will call functions according to the options given in
 * in the command line. 
 *
 * @param argc the number of command line arguments passed in
 * @param argv contains the arguments, starting at index 1, index 0 is the
 *             program name
 */
int main(int argc, char **argv) {

    const char *opstring = "c:deps:t:h";

    extern int optind;

    int tablesize = 113; /*Default snapshots*/
    int num_stats = 10;  /*Default table size*/
    
    char word[256];
    char option;  

    /*arg options*/
    int filename = 0;
    int doublehash = 0;
    int display_contents = 0;
    int print_stat = 0;
    int stats_snapshots = 0;
    int fp_tablesize = 0;

    htable h;

    hashing_t h_method = LINEAR_P; /*Default hashing method is linear probing*/
 
    if(argc > 0) {
        while ((option = getopt(argc, argv, opstring)) != EOF) {
            switch(option) {               
                case 'c':   
                    filename = 1;        
                    break;
                case 'd':
                    doublehash = 1;
                    break;
                case 'e':
                    display_contents = 1; 
                    break;
                case 'p':
                    print_stat = 1;
                    break;
                case 's':
                    stats_snapshots = 1;
                    num_stats = atoi(optarg);                    
                    break;
                case 't':
                    fp_tablesize = 1;
                    tablesize = atoi(optarg);                  
                    break;
                case 'h':
                    print_help_message();
                    break;
                default :
                    print_help_message();
                    exit(EXIT_FAILURE);
            }
        }
    } 
    
    if(fp_tablesize == 1) {
        while(isPrime(tablesize)) {
            tablesize++;
        }
    }

    /**
     * Use double hashing as the collision resolution strategy
     * (linearprobing is the default).
     */
    if(doublehash == 1) {
        h_method = DOUBLE_H;
    }

    h = htable_new(tablesize, h_method);

    if(filename == 0){
	    while(getword(word, sizeof word, stdin) != EOF) {
	        htable_insert(h, word);
	    }
	}

    if(filename == 1) {  
        compare_files(h); 
    }

    /**
     * Display up to the given number of stats snapshots when
     * given-pas an argument. 
     
    if(stats_snapshots == 1) {
        htable_print_stats(h, stdout, num_stats);
    }
    */
    /**
     * Display entire contents of hash table on stderr using
     * the formatstring "%5d␣%5d␣%5d␣␣␣%sn" to display the
     * index, frequency,stats, and the key if it exists.
     */
    if(display_contents == 1) {
        htable_print_entire_table(h, stderr);
    }

    /**
     * Prints stats in an informative table.
     */
    if(print_stat == 1) {
        htable_print_stats(h, stdout, num_stats);
    }

    if(print_stat == 0 && filename != 1) {
        htable_print(h);
    }
    
    htable_free(h);

    return EXIT_SUCCESS;
}
