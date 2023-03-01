//
// Created by downq on 2/21/2023.
//

#ifndef CS327_HEAP_H
#define CS327_HEAP_H

typedef struct node
{
    int key;
    struct node *child;
    struct node *sibling;
    struct node *prev;
    void *data;
} node;

node *createNode(int key, void *data);

node *merge(node *first, node *second);

node *mergePairs(node *first);

node *merge(node *first, node *second);

node *insert(node *root, int key, void *data);

node *deleteMin(node *root);

void traverse(node *root);

void deleteAllData(node *root);

void deleteAll(node *root);

#endif //CS327_HEAP_H
