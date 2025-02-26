#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

/**
 * Author: Aidan Milne-Reeves, Ryan Cole and Jaraz Waerea.
 *
 * This header file contains the function declarations of htable.c.
 */

typedef struct htablerec *htable;
typedef enum hashing_e {LINEAR_P, DOUBLE_H } hashing_t;

extern void        htable_free(htable h);
extern int         htable_insert(htable h, char *str);
extern htable      htable_new(int capacity, hashing_t method);
extern void        htable_print(htable h);
extern int         htable_search(htable h, char *str);
extern void        htable_print_entire_table(htable h, FILE *stream);
extern void        htable_print_stats(htable h, FILE *stream, int num_stats);

#endif
