#ifndef TREEVISION_H
#define TREEVISION_H
#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data);

struct Node* insertBST(struct Node* root, int data);

void freeTree(struct Node* root);

void printTreeVisual(struct Node* root);

void printTraversals(struct Node* root);


#endif 