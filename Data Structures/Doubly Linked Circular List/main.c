#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"CircularDoublyLinkedList.h"

int main(){
    srand(time(NULL));

    List l = createList();
    int n;

    printf("INSERT\n");
    printf("Choose the number of random nodes to insert: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
        insert(&l, rand() % 10 + 1, 0);

    printf("\nPRINT\n");
    printList(&l);
    printf("Size: %i\n", length(&l));

    printf("\nCONSECUTIVE INSERT\n");
    int pos;
    printf("Choose the number of consecutive nodes to insert: ");
    scanf("%i", &n);

    printf("Choose the position to insert the first: ");
    scanf("%i", &pos);

    addConsecutive(&l, pos, n);

    printf("\nPRINT\n");
    printList(&l);
    printf("Size: %i\n", length(&l));

    printf("\nDELETE\n");
    printf("Choose an index to delete: ");
    scanf("%i", &n);
    deleteElement(&l, n);

    printf("\nPRINT\n");
    printList(&l);
    printf("Size: %i\n", length(&l));
    printf("\n");

    printf("\nDELETE\n");
    printf("Choose a number to delete all instances: ");
    scanf("%i", &n);
    deleteValues(&l, n);
    
    printf("\nPRINT\n");
    printList(&l);
    printf("Size: %i\n", length(&l));
    printf("\n");    

    printf("\nSEARCH\n");
    printf("Choose a value to search: ");
    scanf("%i", &n);
    pos = search(&l, n);
    if (pos == -1) {
        printf("Not found\n");
    } else {
        printf("Found at position %i\n", pos);
    }

    printf("\nCHECK IF LIST IS EMPTY\n");
    printf(listIsEmpty(&l) == 1 ? "Empty\n" : "Not Empty\n");

    deleteList(&l);
    return 0;
}