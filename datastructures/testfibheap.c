
#include <stdio.h>
#include <stdlib.h>
#include "fibheap.h"

int main()
{
    // Initialize a new Fibonacci heap
    struct fib_heap *h = fib_heap_init();

    // Create some nodes with keys
    struct fib_heap_node *n1 = fib_heap_make_node(10);
    struct fib_heap_node *n2 = fib_heap_make_node(20);
    struct fib_heap_node *n3 = fib_heap_make_node(30);
    struct fib_heap_node *n4 = fib_heap_make_node(40);
    struct fib_heap_node *n5 = fib_heap_make_node(50);

    // Insert nodes into the heap
    fib_heap_insert(h, n1);
    fib_heap_insert(h, n2);
    fib_heap_insert(h, n3);
    fib_heap_insert(h, n4);
    fib_heap_insert(h, n5);

    // Print the initial heap
    printf("Initial heap:\n");
    fib_heap_print_heap(h);

//    // Extract the minimum node from the heap
//    struct fib_heap_node *min_node = fib_heap_extract_min(h);
//    printf("Extracted minimum node with key %d:\n", min_node->key);
//    free(min_node);
//
//    // Print the updated heap
//    printf("Updated heap:\n");
//    fib_heap_print_heap(h);
//
//    // Insert a new node with a key
//    struct fib_heap_node *n6 = fib_heap_make_node(5);
//    printf("Inserted a new node with key %d:\n", n6->key);
//    fib_heap_insert(h, n6);
//
//    // Print the updated heap
//    printf("Updated heap:\n");
//    fib_heap_print_heap(h);
//
//    // Decrease the key of a node
//    printf("Decreased the key of node %d to %d:\n", n4->key, 15);
//    fib_heap_decrease_key(h, n4, 15);
//
//    // Print the updated heap
//    printf("Updated heap:\n");
//    fib_heap_print_heap(h);
//
//    // Delete a node from the heap
//    printf("Deleted node with key %d:\n", n3->key);
//    fib_heap_delete(h, n3);
//
//    // Print the updated heap
//    printf("Updated heap:\n");
//    fib_heap_print_heap(h);

    // Free the memory used by the heap and its nodes
    fib_heap_free(h);

    return 0;
}

