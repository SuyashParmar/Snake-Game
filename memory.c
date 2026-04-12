#include "snake.h"
#include <stdlib.h> // allowed purely for malloc/free as per plan

struct Node* mem_alloc_node(int x, int y) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node) {
        new_node->x = x;
        new_node->y = y;
        new_node->next = 0; // NULL
    }
    return new_node;
}

void mem_free_node(struct Node* node) {
    if (node) {
        free(node);
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
