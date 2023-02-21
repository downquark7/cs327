
#ifndef CS327_FIBHEAP_H
#define CS327_FIBHEAP_H

// Definition of a node in the Fibonacci heap
struct fib_heap_node
{
    int key;
    struct fib_heap_node *parent;
    struct fib_heap_node *left;
    struct fib_heap_node *right;
    struct fib_heap_node *child;
    int degree;
    int mark;
};

// Definition of the Fibonacci heap data structure
struct fib_heap
{
    struct fib_heap_node *min;
    int n;
};

// Function prototypes for the public API
struct fib_heap *fib_heap_init();

struct fib_heap_node *fib_heap_make_node(int key);

void fib_heap_insert(struct fib_heap *h, struct fib_heap_node *x);

struct fib_heap_node *fib_heap_minimum(struct fib_heap *h);

struct fib_heap_node *fib_heap_extract_min(struct fib_heap *h);

void fib_heap_union(struct fib_heap *h1, struct fib_heap *h2);

void fib_heap_decrease_key(struct fib_heap *h, struct fib_heap_node *x, int k);

void fib_heap_delete(struct fib_heap *h, struct fib_heap_node *x);

void fib_heap_free(struct fib_heap *h);

void fib_heap_consolidate(struct fib_heap *h);

void fib_heap_cut(struct fib_heap *h, struct fib_heap_node *x, struct fib_heap_node *y);

void fib_heap_cascading_cut(struct fib_heap *h, struct fib_heap_node *y);

void fib_heap_print_heap(struct fib_heap *h);

#endif //CS327_FIBHEAP_H
