#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

/**
 * Author: Aidan Milne-Reeves, Ryan Cole and Jaraz Waerea  
 *
 * This file contains the main functions used with the program.
 *
 * @note some of these functions were provided by the lab book and
 *       242 coursework folder
 */

/**
 * A structure that tracks the characteristics of a hash table
 */
struct htablerec {
    int capacity;
    int num_keys;
    int *freq;
    int *stats;
    char **keys;
    hashing_t method;
};

/**
 * Converts a string to an positive integer.
 *
 * @param word the input string
 * @return result a positive integer
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while(*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Method used when double probing is enabled.
 *
 * @param h the hash table
 * @param i_key a positive integer at the current index
 * @return a positive integer
 */
static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

/**
 * This method prints the frequency of a word in the hash table followed by
 * the word itself.
 *
 * @param freq the number of times the word is in the hash table
 * @param word a string for the current word
 */
static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/**
 * This method frees up all memory used in association with the hash table.
 *
 * @param h is the hash table.
 */
void htable_free(htable h) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        if(h->keys[i] != NULL) {
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h->freq);
    free(h);
}

/**
 * This method will insert a string into the hash table by either
 * the linear or double probing methods.
 *
 * @param h is the hash table
 * @param str is the string to be inserted
 * @return 0 if the hash table is full
 * @return 1 if the string is inserted
 * @return the frequency of which the string is inserted
 */
int htable_insert(htable h, char *str) {
    int colls = 0;
    int count = 0;
    unsigned int index = htable_word_to_int(str);
    unsigned int step = htable_step(h, index);
    index = index % h->capacity;
    while(count < h->capacity) {
        if(h->keys[index] == NULL) {
            h->keys[index] = emalloc((strlen(str) + 1) *
                                     sizeof h->keys[index]);
            strcpy(h->keys[index], str);
            h->freq[index]++;
            h->stats[h->num_keys] = colls;
            h->num_keys++;
            return 1;
        } else if (strcmp(h->keys[index], str) == 0) {
            h->freq[index]++;
            return h->freq[index];
        } else {
            colls++;
            count++;
            if(h->method == LINEAR_P) {
                index = (index + 1) % h->capacity;
            }
            else if (h->method == DOUBLE_H) {
                index = (index + step) % h->capacity;
            }
        }
    }
    return 0;
}

/**
 * This method creates a new hash table.
 *
 * @param capacity is the size of the table
 * @param method is the probing method that will be used
 *        to insert the words (default is linear)
 * @return h the hash table
 */
htable htable_new(int capacity, hashing_t method) {
    int i;
    htable h = emalloc(sizeof *h);
    
    h->capacity = capacity;
    h->num_keys = 0;
    h->method = method;
    
    h->freq = emalloc(h->capacity * sizeof h->freq[0]);
    h->keys = emalloc(h->capacity * sizeof h->keys[0]);
    h->stats = emalloc(h->capacity * sizeof h->stats[0]);
    
    for(i = 0; i < capacity; i++) {
        h->freq[i] = 0;
        h->keys[i] = NULL;
        h->stats[i] = 0;
    }
    return h;
}

/**
 * This method will print the entire htable.
 *
 * @param h is the hash table.
 */
void htable_print(htable h) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        if(h->keys[i] != NULL) {
              print_info(h->freq[i], h->keys[i]);
        }
    }
}

/**
 * This searchs the htable for the specified character string.
 *
 * @param h the hash table to be searched
 * @param str the character string we want to find
 * @return 0 if the string is not found
 * @return frequency of which the string is found
 */
int htable_search(htable h, char *str) {
    int coll = 0;
    unsigned int index = htable_word_to_int(str);
    unsigned int step = htable_step(h, index);
    index = index % h->capacity;
    
    while(h->keys[index] != NULL && strcmp(h->keys[index], str) != 0 &&
          coll < h->capacity) {
        coll++;
        if(h->method == LINEAR_P) {
            index = (index + 1) % h->capacity;
        } else if(h->method == DOUBLE_H) {
            index = (index + step) % h->capacity;
        }
    }
    if(coll == h->capacity) {
        return 0;
    } else {
        return h->freq[index];
    }
}

/**
 * Prints out a table showing the position, the frequency and the statistics of
 * every string in the hash table.
 *
 * @li Pos   - the position of the string in the hash table.
 * @li Freq  - how many of the string are at this position.
 * @li Stats - the amount of collisions currently at this position.
 *
 * @param h the hash table to print statistics summary from.
 * @param stream the stream to send output to.
 */
void htable_print_entire_table(htable h, FILE *stream) {
    int i = 0;
    fprintf(stream, "  Pos  Freq  Stats  Word\n");
    fprintf(stream, "------------------------------------------------------\n");
    if(h->keys == NULL) {
        fprintf(stream, "%5d %5d %5d   %s\n", i, h->freq[i],h->stats[i], " ");
    } else {
        for(i = 0; i < h->capacity; i++) {
            if(h->keys[i] == NULL) {
                fprintf(stream, "%5d %5d %5d   %s\n", i, h->freq[i],
                        h->stats[i], "");
            } else {
                fprintf(stream, "%5d %5d %5d   %s\n", i, h->freq[i],
                        h->stats[i], h->keys[i]);
            }
        }
    }
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hash table is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hash table was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hash table to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "------------------------------------------------------"
            "\n\n");
}
