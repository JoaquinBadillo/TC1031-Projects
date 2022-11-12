/*
    Doubly Linked Circular List Header File
*/

#ifndef LIST_H
#define LIST_H

// Nodes and List definition
typedef struct node{
    int value;
    struct node *next;
    struct node *previous;
}node; 

typedef struct List{
    int size;
    node* start;
} List;

// Interface
List createList();
void deleteList(List* list);
void insertStart(List* list, int value);
void insertMiddle(List* list, int value);
void insertEnd(List* list, int value);
void insert(List* list, int value, int pos);
void addConsecutive(List* list, int index, int num);
void deleteElement(List* list, int pos);
void deleteValues(List* list, int x);
int search(List* list, int x);
short listIsEmpty(List* list);
int length(List* list);
void traverseList(List* List);
void printList(List *List);

// Additional Functions
void firstNode(List *List, int value);
void squaredList(List *List);

#endif