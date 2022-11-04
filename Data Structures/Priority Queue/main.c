#include <stdio.h>
#include <stdlib.h>

#include "priorityQueue.h"

void main(void) {
    struct priority_queue* P = Priority_Queue();
    
    int n = 15;
    
    printf("ENQUEUE\n");
    for (int i = 0; i < n; i++) {
        if (isEmpty(P))
            printf("Queue is empty\n");
        enqueue(P, rand() % 10 + 1, i);
        printf("Size: %i\n", size(P));
    }

    printf("\nPrint Queue:\n");
    printPQueue(P);

    printf("\nDEQUEUE\n");
    for (int i = 0; i < n; i++) {
        dequeue(P);
        printf("Size: %i\n", size(P));
        if (isEmpty(P))
            printf("Queue is empty\n");
    }

    printf("\nPrint Queue:\n");
    printPQueue(P);

    deleteQueue(&P);
}
