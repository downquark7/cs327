//
// Created by downq on 2/21/2023.
//

#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

node *create_node(int key, void *data)
{
    node *new_node = (node *) malloc(sizeof(node));
    new_node->key = key;
    new_node->child = NULL;
    new_node->sibling = NULL;
    new_node->prev = NULL;
    new_node->data = data;
    return new_node;
}

node *merge_pairs(node *first)
{
    if (first == NULL || first->sibling == NULL)
    {
        return first;
    }
    node *second = first->sibling;
    node *rest = second->sibling;
    first->sibling = NULL;
    second->sibling = NULL;
    return merge(merge(first, second), merge_pairs(rest));
}

node *merge(node *first, node *second)
{
    if (first == NULL)
    {
        return second;
    }
    if (second == NULL)
    {
        return first;
    }
    if (first->key < second->key)
    {
        second->prev = first;
        first->sibling = merge_pairs(first->sibling);
        second->sibling = NULL;
        first->child = merge(second, first->child);
        return first;
    } else
    {
        first->prev = second;
        second->sibling = merge_pairs(second->sibling);
        first->sibling = NULL;
        second->child = merge(first, second->child);
        return second;
    }
}

node *insert(node *root, int key, void *data)
{
    node *new_node = create_node(key, data);
    return merge(root, new_node);
}

node *delete_min(node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    node *min_node = root;
    node *child = min_node->child;
    while (child != NULL)
    {
        child->prev = NULL;
        child = child->sibling;
    }
    node *new_root = merge_pairs(min_node->child);
    free(min_node->data);
    free(min_node);
    return new_root;
}

void traverse(node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->key);
    traverse(root->child);
    traverse(root->sibling);
}

void delete_all(node *root)
{
    while (NULL != (root = delete_min(root)));
}
