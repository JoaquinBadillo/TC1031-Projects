#include <stdio.h>
#include <stdlib.h>

/* 
    Queue (without priority) header file

    This is a dynamic queue to store elements with the same priority in the RB Tree.
*/

#include "queue.h"

short qIsEmpty(struct queue* q) {
    return q -> front == NULL ? 1 : 0;
}

void qEnqueue(struct queue* q, int x) {
    struct queueNode* element;
    element = (queueNode*)malloc(sizeof(struct queueNode));

    if (element == NULL) {
        printf("Error: No memory.\n");
        return;
    }
    element -> value = x;
    element -> next = NULL;

    if (qIsEmpty(q)) {
        q -> front = element;
        q -> back = element;
    } else {
        (q -> back) -> next = element;
        q -> back = element;
    }
}

int qDequeue(struct queue* q) {
    if (qIsEmpty(q)==1) {
        printf("Error: Empty queue\n");
        return -1;
    }

    struct queueNode* temp;
    temp = q -> front;
    if (q -> front == q -> back) {
        q -> front = NULL;
        q -> back = NULL;
    } else
        q -> front = (q -> front) -> next;
    
    int val = temp -> value;
    free(temp);
    return val;
}

void deleteQueue(struct queue* q) {
    if (q -> front == NULL)
        return;

    queueNode* current = q -> front;

    while (current != NULL) {
        queueNode* temp = current;
        current = current -> next;
        free(temp);
    }

    q -> front = NULL;
    q -> back = NULL;
}

struct queueNode* findQueueNode(struct queue* q, int x) {
    struct queueNode* it;

    for (it = q -> front; it != NULL; it = it -> next)
        if (it -> value == x) {return it;}

    return NULL;
}
