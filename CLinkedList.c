#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode_s {
    char*                    value;
    struct LinkedListNode_s* next;
} LinkedListNode;

typedef struct {
    LinkedListNode* first;
} LinkedList;

LinkedList* new_LinkedList() {
    LinkedList* linked_list = (LinkedList*)malloc(sizeof(LinkedList));
    linked_list->first = NULL;
    return linked_list;
}

void LinkedList_addSorted(LinkedList* linked_list, char* value);

LinkedList* new_sorted_LinkedList(LinkedList* linked_list) {
    LinkedList* sorted = new_LinkedList();
    for (LinkedListNode* i = linked_list->first; i != NULL; i = i->next) {
        LinkedList_addSorted(sorted, i->value);
    }
    return sorted;
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
    // create new node
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);
    // old first is assigned to node next
    node->next = linked_list->first;
    // new node is added to beginning of list (set as first node)
    linked_list->first = node;
}

void LinkedList_addSorted(LinkedList* linked_list, char* value) {
    // create new node
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);
    LinkedListNode* i          = linked_list->first;
    LinkedListNode* previous_i = NULL;
    while (i != NULL) {
        if (strcmp(i->value, value) > 0) {
            // insert node after previous_i or at beginning of list
            if (previous_i == NULL) {
                // old first is assigned to node next
                node->next = linked_list->first;
                // new node is added to beginning of list (set as first node)
                linked_list->first = node;
            } else {
                // preivous i next is assigned to node next
                node->next = previous_i->next;
                // node is assigned to previous i neext
                previous_i->next = node;
            }
            return;
        }
        previous_i = i;
        i = i->next;
    }
    // add the node at the end of the list
    if (previous_i == NULL) {
        // old first is assigned to node next
        node->next = linked_list->first;
        // new node is added to beginning of list (set as first node)
        linked_list->first = node;
    } else {
        // preivous i next is assigned to node next
        node->next = previous_i->next;
        // node is assigned to previous i neext
        previous_i->next = node;
    }
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

void LinkedList_sort(LinkedList* linked_list) {
    // allocate a helper list so that we can do an insertion sort
    LinkedList* helper = new_sorted_LinkedList(linked_list);
    // this is some trickiness!
    LinkedListNode* unsorted_nodes = linked_list->first;
    LinkedListNode* sorted_nodes = helper->first;
    linked_list->first = sorted_nodes;
    helper->first = unsorted_nodes;
    // free the helper list
    free_LinkedList(helper);
}

void LinkedList_print(LinkedList* linked_list, char* name) {
    printf("%s = (", name);
    for (LinkedListNode* i = linked_list->first; i != NULL; i = i->next) {
        if (i != linked_list->first) {
            printf(", ");
        }
        printf("\"%s\"", i->value);
    }
    printf(")\n");
}

LinkedList* new_cities_LinkedList() {
    LinkedList* cities = new_LinkedList();
    // add a value to the beginning of the list
    LinkedList_add(cities, "Moscow");
    // add a value to the beginning of the list
    LinkedList_add(cities, "San Diego");
    // add a value to the beginning of the list
    LinkedList_add(cities, "Emerald Hills");
    // add a value to the beginning of the list
    LinkedList_add(cities, "Keiv");
    // add a value to the beginning of the list
    LinkedList_add(cities, "Molokai");
    // add a value to the beginning of the list
    LinkedList_add(cities, "New York");
    // add a value to the beginning of the list
    LinkedList_add(cities, "Kula");
    return cities;
}

int main(int argc, char** argv) {
    printf("CLinkedList: here.\n");
    // initialize unsorted
    LinkedList* unsorted = new_cities_LinkedList();
    // print unsorted
    LinkedList_print(unsorted, "unsorted");
    // create new sorted LinkedList from unsorted LinkedList
    LinkedList* sorted = new_sorted_LinkedList(unsorted);
    // print sorted
    LinkedList_print(sorted, "sorted");
    // remove value from sorted
    LinkedList_remove(sorted, "Emerald Hills");
    // remove value from sorted
    LinkedList_remove(sorted, "New York");
    // remove value from sorted
    LinkedList_remove(sorted, "Moscow");
    // print sorted
    LinkedList_print(sorted, "sorted");
    // print unsorted
    LinkedList_print(unsorted, "unsorted");
    // free unsprted
    free_LinkedList(unsorted);
    // free sprted
    free_LinkedList(sorted);
    return 0; // success (to bash)
}

