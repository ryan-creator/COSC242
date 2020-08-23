#ifndef QUEUE_H_
#define QUEUE_H_
typedef struct queue *queue;
typedef struct q_item *q_item;

extern queue queue_new();
extern queue queue_free(queue q);
extern void enqueue(queue q, double item);
extern double dequeue(queue q);
extern void queue_print(queue q);
extern void queue_print_info(queue q);
extern void queue_free_aux(q_item i);
extern int queue_size(queue q);
#endif