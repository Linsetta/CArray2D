#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode_s {
    char*                    value;
    struct LinkedListNode_s* next;
} LinkedListNode;

typedef struct LinkedList_s {
    LinkedListNode* first;
} LinkedList;

LinkedList* new_LinkedList() {
    LinkedList* linked_list = (LinkedList*)malloc(sizeof(LinkedList));
    linked_list->first = NULL;
    return linked_list;
}

void free_LinkedList(LinkedList* linked_list) {
    LinkedListNode* i = linked_list->first;
    while (i != NULL) {
        LinkedListNode* next = i->next;
        free(i->value);
        free(i);
        i = next;
    }
    free(linked_list);
}

void LinkedList_add(LinkedList* linked_list, char* value) {
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);
    // old first is assigned to node next
    node->next = linked_list->first;
    // new node is added to beginning of list (set as first node)
    linked_list->first = node;
}

int LinkedList_remove(LinkedList* linked_list, char* value) {
    int count = 0; // the number of values removed
    LinkedListNode* i = linked_list->first;
    LinkedListNode* prev = NULL;
    while (i != NULL) {
        if (strcmp(i->value, value) == 0) {
            // remove and free i
            LinkedListNode* next = i->next;
            if (prev == NULL) {
                linked_list->first = next;
            } else {
                prev->next = next;
            }
            free(i->value);
            free(i);
            count ++;
            i = next;
        } else {
            // skip i
            prev = i;
            i = i->next;
        }
    }
    return count;
}

void LinkedList_print(LinkedList* linked_list) {
    printf("a = (");
    for (LinkedListNode* i = linked_list->first; i != NULL; i = i->next) {
        if (i != linked_list->first) {
            printf(", ");
        }
        printf("\"%s\"", i->value);
    }
    printf(")\n");
}

int main(int argc, char** argv) {
    printf("CLinkedList: here.\n");
    // initialize a
    LinkedList* a = new_LinkedList();
    // add a value to the beginning of the list
    LinkedList_add(a, "Moscow");
    // add a value to the beginning of the list
    LinkedList_add(a, "San Diego");
    // add a value to the beginning of the list
    LinkedList_add(a, "Emerald Hills");
    // add a value to the beginning of the list
    LinkedList_add(a, "Keiv");
    // add a value to the beginning of the list
    LinkedList_add(a, "Molokai");
    // add a value to the beginning of the list
    LinkedList_add(a, "New York");
    // print a
    LinkedList_print(a);
    // remove value from a
    LinkedList_remove(a, "Emerald Hills");
    // remove value from a
    LinkedList_remove(a, "New York");
    // remove value from a
    LinkedList_remove(a, "Moscow");
    // print a
    LinkedList_print(a);
    // free a
    free_LinkedList(a);
    return 0; // success (to bash)
}

