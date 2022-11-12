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

    It was modified to store queues, so that the insertion of multiple nodes is supported in O(lg n + m) time,
    where n is the number of nodes previously stored in the tree and m is the number of nodes to insert.
*/

// RED BLACK TREE INTERFACE

// NIL Sentinel (Following Cormen, et al. implementation)
struct node nil_node = {.key = INT_MAX, .data = 0, .color = BLACK, .parent = &nil_node, .left = &nil_node, .right = &nil_node};
struct node* NIL = &nil_node;

// Constructor -- Time Complexity: O(1)
struct node* Node(int key, int value) { 
    node* element;
    element = malloc(sizeof(node));

    if (element == NULL)
        return NIL;

    element -> key = key;
    element -> data = (queue*)malloc(sizeof(queue));
    qEnqueue(element -> data, value);
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

        deleteQueue(element -> data);
        free(element -> data);

        free(element);
    }
}

// Insertion -- Time Complexity: O(lg k)
struct node* insertNode(struct node** root, int key, int value) {
	node* prev = NIL;
	node* current = *root;

    short insertNewNode = 1;

	while (current != NIL) {
		prev = current;

		if (key < current -> key)
			current = current -> left;
		else if (key > current -> key)
			current = current -> right;
        else {
            insertNewNode = 0;
            break;
        }
	}

    if (insertNewNode) {
        node* element = Node(key, value);

        if (element == NIL) {
            printf("Error: No memory!\n");
            return NULL;
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
    } else {
        qEnqueue(current -> data, value);
        return current;
    }
}

// Deletion -- Time Complexity: O(lg k)
void deleteNode(struct node** root, struct node* z) {
    if (!qIsEmpty(z -> data))
        return;
    
    node *x, *y;
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

    free(z -> data);
    free(z);

    if (yColor == BLACK)
        deleteFixUp(root, x);
}

// In Order Traversal -- Time Complexity: O(n)
void inOrderTraversal(struct node* subtreeRoot) {
    if (subtreeRoot != NIL) {
        inOrderTraversal(subtreeRoot -> left);
        
        queueNode* it;
        for (it = subtreeRoot -> data -> front; it != NULL; it = it -> next)
            printf("(%i, %i) - ", subtreeRoot -> key, it ->value);

        inOrderTraversal(subtreeRoot -> right);
    }
}

// PRIORITY QUEUE INTERFACE

// Constructor -- Time Complexity: O(1)
struct priority_queue* Priority_Queue() {
    priority_queue* P;
    P = malloc(sizeof(struct priority_queue));

    if (P == NULL) {
        return NULL;
    }

    P -> root = NIL;
    P -> size = 0;

    return P;
}

// Destructor -- Time Complexity: O(n)
void deletePQueue(struct priority_queue** P) {
    deleteSubtree(&(P[0] -> root), P[0] -> root);
    free(*P);
    *P = NULL;

    printf("\nPriority queue deleted: Your RAM is safe\n");
}

// Enqueue (with priority) -- Time Complexity: O(lg k)
short enqueue(struct priority_queue* P, int key, int data) {
    node* inserted = insertNode(&(P -> root), key, data);
    if (inserted) {
        P -> size++;
        return 1; 
    }
    printf("Error: could not insert\n");
    return 0;
}

// Dequeue (with priority) -- Time Complexity: O(lg k)
int dequeue(struct priority_queue* P) {
    if (isEmpty(P)) {
        printf("Queue is empty!\n");
        return -1;
    }

    node* x = minimum(P -> root);
    int priority = x -> key;
    int value = qDequeue(x -> data);

    if (qIsEmpty(x -> data))
        deleteNode(&(P -> root), x);
    
    P -> size--;
    printf("Dequeued: (%i, %i)\n", priority, value);
    return value;
}

// Find node -- Time Complexity: O(m lg k)
struct queueNode* findNode(struct priority_queue* P, int key, int data) {
    node* current = P -> root;

    while (P -> root != NIL) {
        if (current -> key < key)
            current = current -> left;
        else if (current -> key > key)
            current = current -> right;
        else {
            queueNode* found = findQueueNode(current -> data, data);
            if (found)
                return found;
            else 
                break;
        }
    }

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
        printf("[FRONT] ");
        inOrderTraversal(P -> root);
        printf("[BACK]\n");
    }
}

// Enqueue Consecutive Nodes -- Time Complexity: O(lg k + m)
void enqueueMultiple(struct priority_queue* P, int key, int* data, int num) {
    node* prev = NIL;
	node* current = P -> root;

    short insertNewNode = 1;

	while (current != NIL) {
		prev = current;

		if (key < current -> key)
			current = current -> left;
		else if (key > current -> key)
			current = current -> right;
        else {
            insertNewNode = 0;
            break;
        }
	}

    if (insertNewNode) {
        node* element = Node(key, data[0]);

        if (element == NIL) {
            printf("Error: No memory!\n");
            return;
        }

        element -> parent = prev; 

        if(prev == NIL)
            P -> root  = element;
        else if (element -> key < prev -> key)
            prev -> left = element;
        else
            prev -> right = element;

        insertFixUp(&(P -> root), element);

        current = element;
        P -> size++;

        printf("Enqueued: (%i, %i)\n", key, data[0]);
    }

    for (int i = insertNewNode; i < num; ++i) {
        qEnqueue(current -> data, data[i]);
        P -> size++;
        printf("Enqueued: (%i, %i)\n", key, data[i]);
    }
}

// HELPER FUNCTIONS

void leftRotate(struct node** root, struct node* x) {
    node* y = x -> right;				
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
    node* x = y -> left;
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
    node* temp;
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
            node* w = x -> parent -> right;

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
                node* w = x -> parent -> left;

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
    node* temp = T;

    while (temp -> left != NIL) {
        temp = temp -> left;
    }

    return temp;
}

struct node* maximum(struct node* T) {
    node* temp = T;

    while (temp -> right != NIL) {
        temp = temp -> right;
    }

    return temp;
}