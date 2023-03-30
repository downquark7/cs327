//
// Created by downq on 2/21/2023.
//

#include "heap.h"
#include <stdlib.h>

node *createNode(unsigned int key, void *data)
{
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = key;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->prev = NULL;
    newNode->data = data;
    return newNode;
}

node *mergePairs(node *first)
{
    if (first == NULL || first->sibling == NULL)
    {
        return first;
    }
    node *second = first->sibling;
    node *rest = second->sibling;
    first->sibling = NULL;
    second->sibling = NULL;
    return merge(merge(first, second), mergePairs(rest));
}

node *merge(node *first, node *second)
{
    if (first == nullptr)
    {
        return second;
    }
    if (second == nullptr)
    {
        return first;
    }
    if (first->key < second->key)
    {
        second->prev = first;
        first->sibling = mergePairs(first->sibling);
        second->sibling = NULL;
        first->child = merge(second, first->child);
        return first;
    } else
    {
        first->prev = second;
        second->sibling = mergePairs(second->sibling);
        first->sibling = NULL;
        second->child = merge(first, second->child);
        return second;
    }
}

node *insert(node *root, unsigned int key, void *data)
{
    node *newNode = createNode(key, data);
    return merge(root, newNode);
}

node *deleteMin(node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    node *minNode = root;
    node *child = minNode->child;
    while (child != NULL)
    {
        child->prev = NULL;
        child = child->sibling;
    }
    node *newRoot = mergePairs(minNode->child);
    free(minNode);
    return newRoot;
}

void traverse(node *root)
{
    if (root == NULL)
    {
        return;
    }
//    printf("%d ", root->key);
    traverse(root->child);
    traverse(root->sibling);
}

void deleteAllData(node *root)
{
    if (root == NULL)
        return;
    free(root->data);
    while (NULL != (root = deleteMin(root)))
    {
        free(root->data);
    }
}

void deleteAll(node *root)
{
    if (root == NULL)
        return;
    while (nullptr != (root = deleteMin(root)));
}
