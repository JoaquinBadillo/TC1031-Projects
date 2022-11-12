/* 
    Queue (without priority) header file
*/

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueNode {
    int value;
    struct queueNode* next;
} queueNode;

typedef struct queue {
    struct queueNode* front;
    struct queueNode* back;
} queue;

// Interface

short qIsEmpty(struct queue* q);
void qEnqueue(struct queue* q, int x);
int qDequeue(struct queue* q);
void deleteQueue(struct queue* q);
struct queueNode* findQueueNode(struct queue* q, int x);

#endif