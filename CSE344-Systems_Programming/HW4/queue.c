#include "queue.h"

void offer_char(Queue **q, char e){
    if(q==NULL) return;

    if((*q)==NULL) {
        (*q) = (Queue*)malloc(sizeof(Queue));
        (*q)->head = NULL;
        (*q)->tail =NULL;
    }

    if((*q)->tail == NULL){
        (*q)->head = (Node*)malloc(sizeof(Node));
        (*q)->tail = (*q)->head;

        (*q)->head->data_hw = e;
        (*q)->head->next = NULL;

        return;
    }

    (*q)->tail->next = (Node*)malloc(sizeof(Node));
    (*q)->tail->next->data_hw = e;
    (*q)->tail->next->next = NULL;
    
    (*q)->tail = (*q)->tail->next;
}

char poll_char(Queue **q){
    char ret_val = -1;

    if(q==NULL || (*q)==NULL || (*q)->head==NULL) {
        return ret_val;
    }

    Node* temp = (*q)->head;
    ret_val = temp->data_hw;
    (*q)->head=(*q)->head->next;

    if((*q)->head == NULL){
        (*q)->tail = NULL;
    }

    free(temp);

    return ret_val;
}

void free_queue(Queue **q){
    if(q==NULL || (*q)==NULL) return;
    Node *temp;
    Node *iter=(*q)->head;
    while(iter != NULL){
        temp = iter;
        iter = iter->next;
        temp->next = NULL;
        free(temp);
    }

    free(*q);
}

int is_empty(Queue **q){
    if(q==NULL || (*q)==NULL || (*q)->head==NULL) return 1;
    
    return 0;
}

void print_queue(Queue *q){
    if(q==NULL) return;
    
    Node *iter = q->head;
    while(iter != NULL){
        printf("%c\n", iter->data_hw);
        iter = iter->next;
    }
}
