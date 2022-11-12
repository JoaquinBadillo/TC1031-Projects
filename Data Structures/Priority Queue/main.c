#include <stdio.h>
#include <stdlib.h>

#include "priorityQueue.h"

void main(void) {
    struct priority_queue* P = Priority_Queue();
    int n;

    printf("ENQUEUE\n");
    printf("Choose the number of random nodes to enqueue: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++) {
        int priority = rand() % 10 + 1;
        if (enqueue(P, priority, i)) {
            printf("Enqueued: (%i, %i)\n", priority, i);
        }
    }
    
    printf("\nPrint Queue:\n");
    printPQueue(P);
    printf("Size: %i\n", size(P));

    printf("\nENQUEUE CONSECUTIVE:\n");
    int values[n];
    int priority;

    printf("Choose the number of consecutive nodes to enqueue: ");
    scanf("%i", &n);

    printf("Choose their priority: ");
    scanf("%i", &priority);

    for (int i = 0; i < n; ++i) {
        printf("Choose a value to insert: ");
        scanf("%i", &values[i]);
    }
    
    enqueueMultiple(P, priority, values, n);

    printf("\nPrint Queue:\n");
    printPQueue(P);
    printf("Size: %i\n", size(P));

    printf("\nSEARCH\n");
    int value;
    printf("Choose the priority of the node: ");
    scanf("%i", &priority);

    printf("Choose the value to search: ");
    scanf("%i", &value);

    printf(findNode(P, priority, value) == NULL ? "Not found\n" : "Found\n");

    printf("\nCHECK IF QUEUE IS EMPTY\n");
    printf(isEmpty(P) == 1 ? "Empty\n" : "Not empty\n");

    printf("\nDEQUEUE\n");
    printf("Choose the number of nodes to dequeue: ");
    scanf("%i", &n);
    for (int i = 0; i < n; i++) {
        int data = dequeue(P);
    }

    printf("\nPrint Queue:\n");
    printPQueue(P);
    printf("Size: %i\n", size(P));

    printf("\nCHECK IF QUEUE IS EMPTY\n");
    printf(isEmpty(P) ? "Empty\n" : "Not empty\n");

    deletePQueue(&P);
}
