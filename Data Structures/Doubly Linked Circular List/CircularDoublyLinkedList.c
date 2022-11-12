/*
    Doubly Linked Circular List Implementation
*/

#include<stdio.h>
#include<stdlib.h>

#include"CircularDoublyLinkedList.h"

List createList(){
    List list;
    list.start = NULL;
    list.size = 0;
    return list;
}

void deleteList(List *list){
    if (listIsEmpty(list))
        printf("List is empty\n");
    else {
        node* temp = list -> start;
        while(temp -> next != list -> start){
            temp = temp -> next;
            free(temp -> previous);
        }
        free(temp);
        list -> start = NULL;
        printf("List deleted, your RAM is safe\n");
    }
}

// Insert at the beginning -- O(1)
void insertStart(List *list, int value){
    if(listIsEmpty(list))
        firstNode(list, value);
    else {
        node* newNode;
        newNode = (node*)malloc(sizeof(node));

        newNode -> value = value;
        newNode -> next = list -> start;
        newNode -> previous = list -> start -> previous;
        
        newNode -> next -> previous = newNode;
        newNode -> previous -> next = newNode;

        list -> start = newNode;
        list -> size++;
    }
}

// Insert in the middle -- O(n)
void insertMiddle(List *list, int value){ 
    if(listIsEmpty(list))
        firstNode(list, value);
    else {
        int length = list -> size / 2;
        
        node *newNode, *temp;
        newNode = (node*)malloc(sizeof(node));
        temp = list -> start;

        for (int i = 0; i < length; i++)
            temp = temp -> next;

        newNode -> value = value;
        newNode -> next = temp -> next;
        newNode -> previous = temp -> previous;

        newNode -> next -> previous = newNode;
        temp -> next = newNode;
        
        list -> size++;
    }
}

// Insert at the end -- O(1)
void insertEnd(List *list, int value){ 
    if(listIsEmpty(list))
        firstNode(list, value);
    else {
        node *newNode, *temp;
        newNode = (node*)malloc(sizeof(node));

        newNode -> value = value;
        newNode -> next = list -> start;
        newNode -> previous = list -> start -> previous;

        newNode -> next -> previous = newNode;
        newNode -> previous -> next = newNode;

        list -> start -> previous = newNode;
        temp = list->start;
        
        list -> size++;
    }
}

// Insert at a desired position -- O(n)
void insert(List *list, int value, int pos) {
    if(listIsEmpty(list))
        firstNode(list, value);
    else if (pos == 0)
        insertStart(list, value);
    else {
        int length = pos % list -> size;
        
        node *newNode, *temp;
        newNode = (node*)malloc(sizeof(node));
        temp = list -> start;

        for (int i = 0; i < length; i++)
            temp = temp -> next;

        newNode -> value = value;
        newNode -> next = temp -> next;
        newNode -> previous = temp -> previous;

        newNode -> next -> previous = newNode;
        newNode -> previous -> next = newNode;
        
        list -> size++; 
    }
}

// Insert consecutive nodes -- O(k)
void addConsecutive(List *list, int index, int num){
    int first = (int)listIsEmpty(list);
    int pos;
    
    if (first) {
        int value;
        printf("Type the value of the element: ");
        scanf("%d", &value);
        firstNode(list, value);
        pos = 0;
    } else if (index == 0) {
        int value;
        printf("Type the value of the element: ");
        scanf("%i", &value);
        insertStart(list, value);
        first = 1;
        pos = 1;
    } else {
        pos = index % list -> size;
    }
     
    node* temp = list -> start;
    int i;

    for (i = 0; i < pos - 1; ++i)
        temp = temp -> next;

    for (i = first; i < num; ++i) {
        int value;
        printf("Type the value of the element: ");
        scanf("%d", &value);

        node* newNode = (node*)malloc(sizeof(node*));

        if (newNode == NULL) {
            printf("No memory\n");
            return;
        }

        newNode -> value = value;
        newNode -> previous = temp;
        newNode -> next = temp -> next;
        temp -> next = newNode;
        temp = newNode;

        list -> size++;
    }
    
}

// Delete item by position -- O(n)
void deleteElement(List *list, int pos){
    if(listIsEmpty(list)){
        printf("The list is empty\n");
        return;
    } else {
        node *temp = list -> start;
        pos = pos % list -> size;

        for(int i = 0; i < pos; ++i)
            temp = temp -> next;

        if (--(list -> size) == 0) {
            list -> start = NULL;
        } else if (pos == 0) {
            list -> start = temp -> next;
        }
        
        temp -> previous -> next = temp -> next;
        temp -> next -> previous = temp -> previous;

        free(temp);
    }
}

// Delete all items with the given value -- O(n)
void deleteValues(List *list, int x) {
    node* current = list -> start;
    int i;
    int counter = 0;
    
    for (i = 0; i < list -> size; ++i){
        if (current -> value == x) {
            node* temp = current;
            current = current -> next; 

            temp -> next -> previous = temp -> previous;
            temp -> previous -> next = temp -> next;

            free(temp);
            ++counter;

            if (i == 0) {
                list -> start = current;
            }         
        } else {
            current = current -> next;
        } 
    }

    list -> size -= counter;

    if (list -> size == 0)
        list -> start = NULL;
}

// Find value -- O(n)
int search(List* list, int x) {
    node* current = list -> start;
    int i;

    for (i = 0; i < list -> size; ++i){
        if (current -> value == x)
            return i;
        
        current = current -> next;
    }

    return -1;
}

// Check if list is empty -- O(1)
short listIsEmpty(List *list){
    return list -> size == 0 ? 1 : 0;
}

// Get number of nodes -- O(1)
int length(List *list){
    return list->size;
}

// Traverse list -- O(n)
void traverseList(List *list){
    int var = 0;
    node *temporal = list->start;
    do{
        printf("Current element is: %d \n", temporal->value);
        printf("To show previous press [1]\n");
        printf("To show next press [2]\n");
        printf("To exit press any other number\n");
        scanf("%d", &var);
        temporal = var == 1 ? temporal -> previous : temporal -> next;
    } while(var == 1 || var == 2);
}

// Print list -- O(n)
void printList(List *list){
    int size = list->size;
    if(listIsEmpty(list)){
        printf("The list is empty\n");
        return;
    }else{
        printf("Elements of the list\n");
        node *actual = list -> start; 
        while(size != 0) {
            printf("%d\n", actual -> value);
            actual = actual -> next;
            size--;
        }
    }
}

// Additional Functions

void firstNode(List *list, int value){
    node *nodo = (node*)malloc(sizeof(node));
    nodo->value = value;
    nodo->next = nodo;
    nodo->previous = nodo;
    list->start = nodo;
    list->size++;
}

void squaredList(List *list){
    node *temporal = list->start;
    do{
        temporal->value *= temporal->value;
        temporal = temporal->next;
    }while(temporal != list->start);
}