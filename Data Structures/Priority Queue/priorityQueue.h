/* 
    Priority Queue header file
*/

#ifndef PQUEUE_H
#define PQUEUE_H

#define RED 'R'
#define BLACK 'B'

// Nodes and Queue definition
typedef struct node {
    int key; // Priority
    int data; // Value

    char color;
    struct node* parent;
    struct node* left;
    struct node* right;
} node;

typedef struct priority_queue {
    struct node* root;
    int size;
} priority_queue;

// Tree Interface
struct node* Node();
void deleteSubtree(struct node** root, struct node*);
struct node* insertNode(struct node** root, int key, int data);
void deleteNode(struct node** root, struct node* z);
void inOrderTraversal(struct node* root);

// Priority Queue Interface
struct priority_queue* Priority_Queue();
void deleteQueue(struct priority_queue** P);
void enqueue(struct priority_queue* P, int key, int data);
int dequeue(struct priority_queue* P);

// Additonal Functions
struct node* findNode(struct priority_queue* P, int key, int data);
short isEmpty(struct priority_queue* P);
int size(struct priority_queue* P);
void printPQueue(struct priority_queue* P);

// Helper Functions
void leftRotate(struct node** tree, struct node* x); 
void rightRotate(struct node** tree, struct node* y);
void insertFixUp(struct node** tree, struct node* z);
struct node* minimum(struct node* subtree);
struct node* maximum(struct node* subtree);
void transplant(struct node** tree, struct node* u, struct node* v);
void deleteFixUp(struct node** tree, struct node* x);

#endif