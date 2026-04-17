#include "snake.h"

#define MAX_MEM_NODES 1000

static struct Node mem_pool[MAX_MEM_NODES];
static int node_used[MAX_MEM_NODES] = {0};

struct Node* mem_alloc_node(int x, int y) {
    for (int i = 0; i < MAX_MEM_NODES; ++i) {
        if (!node_used[i]) {
            node_used[i] = 1;
            struct Node* new_node = &mem_pool[i];
            new_node->x = x;
            new_node->y = y;
            new_node->next = 0; // NULL
            return new_node;
        }
    }
    return 0; // NULL if out of memory
}

void mem_free_node(struct Node* node) {
    if (node) {
        for (int i = 0; i < MAX_MEM_NODES; ++i) {
            if (&mem_pool[i] == node) {
                node_used[i] = 0;
                break;
            }
        }
    }
}

void mem_free_list(struct Node* head) {
    struct Node* current = head;
    while (current != 0) { // iterate till NULL
        struct Node* next = current->next;
        mem_free_node(current);
        current = next;
    }
}
