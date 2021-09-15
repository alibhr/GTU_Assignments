#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char data_hw;
    struct Node *next;
}Node;

typedef struct Queue{
    struct Node *head;
    struct Node *tail;
}Queue;

void offer_char(Queue **q, char e);
char poll_char(Queue **q);
void free_queue(Queue **q);
int is_empty(Queue **q);

void print_queue(Queue *q);

#endif
