#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE ((int)INT_MAX)

typedef struct DoublyLinkedListNode_s DoublyLinkedListNode;
struct DoublyLinkedListNode_s {
    DoublyLinkedListNode* forward;
    int                   data;
    DoublyLinkedListNode* back;
};

DoublyLinkedListNode* new_doubly_linked_list() {
    DoublyLinkedListNode* list = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    list->forward = list;
    list->data    = DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE;
    list->back    = list;
    return list;
}

void free_doubly_linked_list(DoublyLinkedListNode* list) {
    DoublyLinkedListNode* i = list->forward;
    while (i->data != DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE) {
        DoublyLinkedListNode* forward = i->forward;
        free(i);
        i = forward;
    }
    free(list);
}

void doubly_linked_list__traverse(DoublyLinkedListNode* list) {
    printf("[");
    DoublyLinkedListNode* i = list->forward;
    int index = 0;
    while (i->data != DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE) {
        if (index != 0) {
            printf(", ");
        }
        printf("%d", i->data);
        i = i->forward;
        index ++;
    }
    printf("]\n");
}

// sorted insert
void doubly_linked_list__insert(DoublyLinkedListNode* list, int data) {
    DoublyLinkedListNode* new_node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    new_node->data = data;
    DoublyLinkedListNode* previous = list;
    DoublyLinkedListNode* i        = list->forward;
    while (i->data != DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE) {
        if (data < i->data) {
            // insert node before i in list
            previous->forward = new_node;
            new_node->back = previous;
            new_node->forward = i;
            i->back = new_node;
            return;
        }
        previous = i;
        i = i->forward;
    }
    // insert node at end of list
    previous->forward = new_node;
    new_node->back = previous;
    new_node->forward = i;
    i->back = new_node;
}

int main(int argc, char** argv) {
    printf("CDoublyLinkedList: here.\n");
    DoublyLinkedListNode* list = new_doubly_linked_list();
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 2);
    doubly_linked_list__insert(list, 1);
    printf("sentinel_node = ");
    doubly_linked_list__traverse(list);
    free_doubly_linked_list(list);
    return 0; // success (to bash)
}

