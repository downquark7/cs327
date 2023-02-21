
#include "fibheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct fib_heap *fib_heap_init()
{
    struct fib_heap *h = (struct fib_heap *) malloc(sizeof(struct fib_heap));
    h->min = NULL;
    h->n = 0;
    return h;
}

void fib_heap_link(struct fib_heap_node *y, struct fib_heap_node *x)
{
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL)
    {
        x->child = y;
        y->left = y;
        y->right = y;
    } else
    {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right = y;
        y->right->left = y;
    }
    x->degree++;
    y->mark = 0;
}

void fib_heap_insert(struct fib_heap *h, struct fib_heap_node *x)
{
    if (h->min == NULL)
    {
        h->min = x;
        x->left = x;
        x->right = x;
    } else
    {
        x->left = h->min;
        x->right = h->min->right;
        h->min->right = x;
        x->right->left = x;
        if (x->key < h->min->key)
        {
            h->min = x;
        }
    }
    h->n++;
}

struct fib_heap_node *fib_heap_minimum(struct fib_heap *h)
{
    return h->min;
}

void fib_heap_union(struct fib_heap *h, struct fib_heap *h1)
{
    if (h->min == NULL)
    {
        h->min = h1->min;
        h->n = h1->n;
    } else if (h1->min != NULL)
    {
        h->min->left->right = h1->min->right;
        h1->min->right->left = h->min->left;
        h->min->left = h1->min;
        h1->min->right = h->min;
        if (h1->min->key < h->min->key)
        {
            h->min = h1->min;
        }
        h->n += h1->n;
    }
}

struct fib_heap_node *fib_heap_extract_min(struct fib_heap *h)
{
    struct fib_heap_node *z = h->min;
    if (z != NULL)
    {
        struct fib_heap_node *x = z->child;
        struct fib_heap_node *tmp;
        while (z->degree > 0)
        {
            tmp = x->right;
            fib_heap_link(x, z->parent);
            x = tmp;
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right)
        {
            h->min = NULL;
        } else
        {
            h->min = z->right;
            fib_heap_consolidate(h);
        }
        h->n--;
    }
    return z;
}

void fib_heap_consolidate(struct fib_heap *h)
{
    int max_degree = log(h->n) / log(2) + 1;
    struct fib_heap_node *A[max_degree];
    for (int i = 0; i < max_degree; i++)
    {
        A[i] = NULL;
    }

    struct fib_heap_node *w = h->min;
    struct fib_heap_node *x, *y, *tmp;
    int d;

    do
    {
        x = w;
        d = x->degree;

        while (A[d] != NULL)
        {
            y = A[d];
            if (x->key > y->key)
            {
                tmp = x;
                x = y;
                y = tmp;
            }
            fib_heap_link(x, y);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        w = w->right;
    } while (w != h->min);

    h->min = NULL;

    for (int i = 0; i < max_degree; i++)
    {
        if (A[i] != NULL)
        {
            if (h->min == NULL)
            {
                h->min = A[i];
            } else
            {
                fib_heap_insert(h, A[i]);
                if (A[i]->key < h->min->key)
                {
                    h->min = A[i];
                }
            }
        }
    }
}


void fib_heap_decrease_key(struct fib_heap *h, struct fib_heap_node *x, int k)
{
    if (k > x->key)
    {
        return;
    }
    x->key = k;
    struct fib_heap_node *y = x->parent;
    if (y != NULL && x->key < y->key)
    {
        fib_heap_cut(h, x, y);
        fib_heap_cascading_cut(h, y);
    }
    if (x->key < h->min->key)
    {
        h->min = x;
    }
}

void fib_heap_cut(struct fib_heap *h, struct fib_heap_node *x, struct fib_heap_node *y)
{
    if (x == x->right)
    {
        y->child = NULL;
    } else
    {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
        {
            y->child = x->right;
        }
    }
    y->degree--;
    x->parent = NULL;
    x->left = h->min;
    x->right = h->min->right;
    h->min->right = x;
    x->right->left = x;
    x->mark = 0;
}

void fib_heap_cascading_cut(struct fib_heap *h, struct fib_heap_node *y)
{
    struct fib_heap_node *z = y->parent;
    if (z != NULL)
    {
        if (y->mark == 0)
        {
            y->mark = 1;
        } else
        {
            fib_heap_cut(h, y, z);
            fib_heap_cascading_cut(h, z);
        }
    }
}

int fib_heap_get_min_key(struct fib_heap *h)
{
    if (h == NULL || h->min == NULL)
    {
        return -1;
    }
    return h->min->key;
}

struct fib_heap_node *fib_heap_get_min_node(struct fib_heap *h)
{
    return h->min;
}

int fib_heap_is_empty(struct fib_heap *h)
{
    return h->n == 0;
}

int fib_heap_get_size(struct fib_heap *h)
{
    return h->n;
}

void fib_heap_print(struct fib_heap_node *node, int depth)
{
    int i;
    for (i = 0; i < depth; i++)
    {
        printf(" ");
    }
    printf("%d\n", node->key);
    struct fib_heap_node *child = node->child;
    if (child != NULL)
    {
        fib_heap_print(child, depth + 1);
        child = child->right;
        while (child != node->child)
        {
            fib_heap_print(child, depth + 1);
            child = child->right;
        }
    }
}

void fib_heap_print_heap(struct fib_heap *h)
{
    if (h->min == NULL)
    {
        printf("Empty heap\n");
    } else
    {
        struct fib_heap_node *node = h->min;
        do
        {
            fib_heap_print(node, 0);
            node = node->right;
        } while (node != h->min);
    }
}

// Create a new node with a given key
struct fib_heap_node *fib_heap_make_node(int key)
{
    struct fib_heap_node *x = (struct fib_heap_node *) malloc(sizeof(struct fib_heap_node));
    x->key = key;
    x->parent = NULL;
    x->left = x;
    x->right = x;
    x->child = NULL;
    x->degree = 0;
    x->mark = 0;
    return x;
}

// Remove a node from the heap entirely
void fib_heap_delete(struct fib_heap *h, struct fib_heap_node *x)
{
    // Decrease the key of the node to negative infinity
    fib_heap_decrease_key(h, x, -2147483648);

    // Extract the minimum node from the heap (which is now the node we just decreased)
    fib_heap_extract_min(h);

    // Free the memory used by the node
    free(x);
}

void fib_free_recursive(struct fib_heap_node *node)
{
    if (node == NULL)
        return;
    if (node->child != NULL)
    {
        fib_free_recursive(node->child);
    } else
    {
        node->parent->child = NULL;
        node->left->right = NULL;
    }

    struct fib_heap_node *root = node;
    node = node->right;
    while (node != NULL && node != root)
    {
        fib_free_recursive(node);
        node = node->right;
    }

    printf("freeing %d\n", root->key);
    free(root);
}


void fib_heap_free(struct fib_heap *h)
{
//    struct fib_heap_node *root = fib_heap_get_min_node(h);
//    fib_free_recursive(root);
    while (!fib_heap_is_empty(h))
    {
        printf("key %d\n", fib_heap_extract_min(h)->key);
        fib_heap_print_heap(h);
    }
    free(h);
}