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

// constructor for creating doubly linked list with two sentinel nodes
//DoublyLinkedListNode* new_doubly_linked_list() {
//    DoublyLinkedListNode* front = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
//    DoublyLinkedListNode* end   = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
//    front->forward              = end;
//    front->data                 = DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE;
//    front->back                 = NULL;
//    end->forward                = NULL;
//    end->data                   = DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE;
//    end->back                   = front;
//    return front;
//}

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

void doubly_linked_list__traverse_forward(DoublyLinkedListNode* list) {
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
int doubly_linked_list__insert(DoublyLinkedListNode* list, int data) {
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
            return 0; // no duplicate exists
        } else if (data == i->data) {
            return 1; // duplicate exists
        }
        previous = i;
        i = i->forward;
    }
    // insert node at end of list
    previous->forward = new_node;
    new_node->back = previous;
    new_node->forward = i;
    i->back = new_node;
    return 0; // no duplicate exists
}

int doubly_linked_list__find(DoublyLinkedListNode* list, int data) {
    DoublyLinkedListNode* iter = list->forward;
    while (iter->data != DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE) {
        if (iter->data == data) {
            return 1; // data found
        }
        iter = iter->forward;
    }
    return 0; // data not found
}

int doubly_linked_list__delete(DoublyLinkedListNode* list, int data) {
    DoublyLinkedListNode* iter = list->forward;
    while (iter->data != DOUBLY_LINKED_LIST_NODE_SENTINEL_VALUE) {
        if (iter->data == data) {
            iter->back->forward = iter->forward;
            iter->forward->back = iter->back;
            free(iter);
            return 1; // data found
        }
        iter = iter->forward;
    }
    return 0; // data not found
}

int main(int argc, char** argv) {
    printf("CDoublyLinkedList: here.\n");
    DoublyLinkedListNode* list = new_doubly_linked_list();
    doubly_linked_list__insert(list, 2);
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 3);
    doubly_linked_list__insert(list, 1);
    doubly_linked_list__insert(list, 1);
    doubly_linked_list__insert(list, 1);
    doubly_linked_list__insert(list, 1);
    doubly_linked_list__insert(list, 1);
    doubly_linked_list__insert(list, 4);
    printf("list = ");
    doubly_linked_list__traverse_forward(list);
    doubly_linked_list__delete(list, 1);
    doubly_linked_list__delete(list, 2);
    doubly_linked_list__delete(list, 3);
    printf("list = ");
    doubly_linked_list__traverse_forward(list);
    if (doubly_linked_list__find(list, 4)) {
        printf("found 4!\n");
    } else {
        printf("did not find 4!\n");
    }
    free_doubly_linked_list(list);
    return 0; // success (to bash)
}

