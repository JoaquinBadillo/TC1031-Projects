#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "priorityQueue.h"

/*
    Priority Queue Implementation 
    It uses a Red Black Tree to maintain a Binary Search Tree with logarithmic height.
    This is important as it supports insertion, deletion and search in O(lg n) time
    The enqueue operation is just an insertion thus it takes O(lg n) time
    The dequeue operation searches the minimum key and deletes it, thus it takes O(lg n) time 

    The Red Black Tree follows H. Cormen, Charles E. Leiserson, Ronald L. Rivest & Clifford Stein
    Introduction to Algorithms' implementation.
*/

// RED BLACK TREE INTERFACE

// NIL Sentinel (Following Cormen, et al. implementation)
struct node nil_node = {.key = INT_MAX, .data = 0, .color = BLACK, .parent = &nil_node, .left = &nil_node, .right = &nil_node};
struct node* NIL = &nil_node;

// Constructor -- Time Complexity: O(1)
struct node* Node(int key, int data) { 
    struct node* element;
    element = malloc(sizeof(struct node));

    if (element == NULL)
        return NIL;

    element -> key = key;
    element -> data = data;
    element -> color = RED;

    element -> left = NIL;
    element -> right = NIL;
    element -> parent = NIL;

    return element;
}

// Destructor -- Time Complexity: O(n)
void deleteSubtree(struct node** root, struct node* element) {
    if (element != NIL) {
        deleteSubtree(root, element -> left);
        deleteSubtree(root, element -> right);
        if (element == *root) {
            *root = NIL;
        }
        free(element);
    }
}

// Insertion -- Time Complexity: O(lg n)
struct node* insertNode(struct node** root, int key, int data) {
    struct node* element = Node(key, data);

    if (element == NIL) {
        printf("Error: No memory!\n");
        return NULL;
    }

	struct node* prev = NIL;
	struct node* current = *root;

	while (current != NIL) {
		prev = current;

		if (element -> key < current -> key)
			current = current -> left;
		else
			current = current -> right;
	}

	element -> parent = prev; 

	if(prev == NIL)
		*root  = element;
	else if (element -> key < prev -> key)
		prev -> left = element;
	else
		prev -> right = element;

	insertFixUp(root, element);

    return element;
}

// Deletion -- Time Complexity: O(lg n)
void deleteNode(struct node** root, struct node* z) {
    struct node *x, *y;
    y = z;

    char yColor = y -> color;

    if (z -> left == NIL) {
        x = z -> right;
        transplant(root, z, z -> right);
    } else if (z -> right == NIL) {
        x = z -> left;
        transplant(root, z, z -> left);
    } else {
        y = minimum(z -> right);
        yColor = y -> color;
        x = y -> right;

        if (y -> parent == z)
            x -> parent = y;
        else {
            transplant(root, y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }

        transplant(root, z, y);

        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
    }

    free(z);

    if (yColor == BLACK)
        deleteFixUp(root, x);
}

// In Order Traversal -- Time Complexity: O(n)
void inOrderTraversal(struct node* subtreeRoot) {
    if (subtreeRoot != NIL) {
        inOrderTraversal(subtreeRoot -> right);
        printf("-> (%i, %i) ", subtreeRoot -> key, subtreeRoot -> data);
        inOrderTraversal(subtreeRoot -> left);
    }
}

// PRIORITY QUEUE INTERFACE

// Constructor -- Time Complexity: O(1)
struct priority_queue* Priority_Queue() {
    struct priority_queue* P;
    P = malloc(sizeof(struct priority_queue));

    if (P == NULL) {
        return NULL;
    }

    P -> root = NIL;
    P -> size = 0;

    return P;
}

// Destructor -- Time Complexity: O(n)
void deleteQueue(struct priority_queue** P) {
    deleteSubtree(&(P[0] -> root), P[0] -> root);
    free(*P);
    *P = NULL;
}

// Enqueue (with priority) -- Time Complexity: O(lg n)
void enqueue(struct priority_queue* P, int key, int data) {
    struct node* inserted = insertNode(&(P -> root), key, data);
    if (inserted) {
        P -> size++; 
        printf("Enqueued: (%i, %i)\n", key, data);
    }
}

// Dequeue (with priority) -- Time Complexity: O(lg n)
int dequeue(struct priority_queue* P) {
    if (isEmpty(P)) {
        printf("Queue is empty!\n");
        return -1;
    }

    struct node* x = minimum(P -> root);
    int priority = x -> key;
    int value = x -> data;
    deleteNode(&(P -> root), x);
    P -> size--;
    printf("Dequeued: (%i, %i)\n", priority, value);
    return value;
}

// Find node -- Time Complexity: O(lg n)
struct node* findNode(struct priority_queue* P, int key, int data) {
    struct node* current = P -> root;

    while (P -> root != NIL) {
        if (current -> key < key)
            current = current -> left;
        else if (current -> key > key)
            current = current -> right;
        else if (current -> data != data)
            current = current -> right;
        else
            return current;
    }

    printf("Node not found\n");
    return NULL;
}

// Determine if PQueue is empty -- Time Complexity: O(1)
short isEmpty(struct priority_queue* P) {
    return P -> size == 0 ? 1 : 0;
}

// Determine the size of the PQueue -- Time Complexity: O(1)
int size(struct priority_queue* P) {
    return P -> size;
}

// Show Queue -- Time Complexity: O(n)
void printPQueue(struct priority_queue* P) {
    if (isEmpty(P))
        printf("Queue is empty\n");
    else {
        printf("[BACK] ");
        inOrderTraversal(P -> root);
        printf("[FRONT]\n");
    }
}

// HELPER FUNCTIONS

void leftRotate(struct node** root, struct node* x) {
    struct node* y = x -> right;				
	x -> right = y -> left;

	if (y -> left != NIL)
		y -> left -> parent = x;

	y -> parent = x -> parent;

	if (x -> parent == NIL)
		*root = y;
	else if(x == x -> parent -> left)
		x -> parent -> left = y;
	else 
		x -> parent -> right = y;

	y -> left = x;
	x -> parent = y; 
}

void rightRotate(struct node** root, struct node* y) {
    struct node* x = y -> left;
	y -> left = x -> right;

	if(x -> right != NIL)
		x -> right -> parent = y;

	x -> parent = y -> parent;

	if(y -> parent == NIL)
		*root = x;
	else if( y == y -> parent -> right )
		y -> parent -> right = x;
	else
		y -> parent -> left = x;


	x -> right = y;
	y -> parent = x;
}

void insertFixUp(struct node** root, struct node* z) {
    struct node* temp;
    int counter = 0;
    while (z -> parent -> color == RED) {
        if (z -> parent == z -> parent -> parent -> left) {
            temp = z -> parent -> parent -> right;

            if (temp -> color == RED) {
                z -> parent -> color = BLACK;
                temp -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;

            } else {

                if (z == z -> parent -> right) {
                    z = z -> parent;
                    leftRotate(root, z);
                }

                z -> parent -> color = BLACK;
                z -> parent -> parent -> color = RED;
                rightRotate(root, z -> parent -> parent);
            }
        } else {
            temp = z -> parent -> parent -> left;

            if (temp -> color == RED) {
                z -> parent -> color = BLACK;
                temp -> color = BLACK;
                z -> parent -> parent -> color = RED;
                z = z -> parent -> parent;
            } else {

                if (z == z -> parent -> left) {
                    z = z -> parent;
                    rightRotate(root, z);
                }

                z -> parent -> color = BLACK;
                z -> parent -> parent -> color = RED;
                leftRotate(root, z -> parent -> parent);
            }
        }
    }

    root[0] -> color = BLACK;
}

void deleteFixUp(struct node** root, struct node* x) {

    while ((x != *root) && (x -> color == BLACK)) {

        if (x == x -> parent -> left) {
            struct node* w = x -> parent -> right;

            if (w -> color == RED) {
                w -> color = BLACK;
                x -> parent -> color = RED;
                leftRotate(root, x -> parent);
                w = x -> parent -> right;
            }

            if ((w -> left -> color == BLACK) && (w -> right -> color == BLACK)) {
                w -> color = RED;
                x = x -> parent;
            } else {

                if (w -> right -> color == BLACK) {
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    rightRotate(root, w);
                    w = x -> parent -> right;
                }

                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                leftRotate(root, x -> parent);
                x = *root;      
            }
        } else {

            if (x == x -> parent -> right) {
                struct node* w = x -> parent -> left;

                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rightRotate(root, x -> parent);
                    w = x -> parent -> left;
                }

                if ((w -> right -> color == BLACK) && (w -> left -> color == BLACK)) {
                    w -> color = RED;
                    x = x -> parent;
                } else {

                    if (w -> left -> color == BLACK) {
                        w -> right -> color = BLACK;
                        w -> color = RED;
                        leftRotate(root, w);
                        w = x -> parent -> left;
                    }

                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> left -> color = BLACK;
                    rightRotate(root, x -> parent);
                    x = *root;  
                }     
            }
        }
    }

    x -> color = BLACK;
}

void transplant(struct node** root, struct node* u, struct node* v) {
    if (u -> parent == NIL)
        *root = v;
    else if (u == u -> parent -> left)
        u -> parent -> left = v;
    else
        u -> parent -> right = v;
    
    v -> parent = u -> parent;
}

struct node* minimum(struct node* T) {
    struct node* temp = T;

    while (temp -> left != NIL) {
        temp = temp -> left;
    }

    return temp;
}

struct node* maximum(struct node* T) {
    struct node* temp = T;

    while (temp -> right != NIL) {
        temp = temp -> right;
    }

    return temp;
}