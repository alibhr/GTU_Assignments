#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data_hw;
    struct Node *next;
}Node;

typedef struct Queue{
    struct Node *head;
    struct Node *tail;
}Queue;

void offer_int(Queue **q, int e);
int poll_int(Queue **q);
void free_queue(Queue **q);
int is_empty(Queue **q);

void print_queue(Queue *q);

#endif
