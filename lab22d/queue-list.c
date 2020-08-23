#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

struct q_item {
	double item;
	q_item next;
};

struct queue {
	q_item first;
	q_item last;
	int length;
};

queue queue_new() {
	queue q = emalloc(sizeof *q);

	q -> first = NULL;
	q -> last = NULL;
	q -> length = 0;

	return q;
}

void enqueue(queue q, double item) {
q_item i = emalloc(sizeof *i);
i->item = item;
i->next = NULL;
if (q->length == 0) {
q->first = i;
} else {
q->last->next = i;
}
q->last = i;

q->length++;
}

double dequeue(queue q) {
	q_item deq_item;
	double value;

	deq_item = q -> first;
	value = deq_item -> item;

	q -> first = q -> first -> next;
	q -> length--;

	free(deq_item);

	return value;
}

void queue_print(queue q) {
/* print queue contents one per line to 2 decimal places */
	if(q -> length > 0){
		q_item temp = q -> first;
		while(temp != NULL){
			printf("%.2f\n", temp -> item);
			temp = temp -> next;
		}
	}
}
void queue_print_info(queue q) {
if (q->length == 0) {
printf("The queue is empty\n");
} else {
printf("first %.2f, last %.2f, length %d\n", q->first->item,
q->last->item, q->length);
}
}
int queue_size(queue q) {
	return q -> length;
}
void queue_free_aux(q_item i) {
	if(i -> next != NULL){
		queue_free_aux(i -> next);
	}
	free(i);
}
queue queue_free(queue q) {
	if(q -> length != 0){
		queue_free_aux(q -> first);
	}
	free(q);
	return q;
}