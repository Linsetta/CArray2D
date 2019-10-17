#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack_s Stack;

struct Stack_s {
    char*           value;
    struct Stack_s* next;
};

void create_Stack(Stack** stack) {
    *stack = NULL;
}

void free_Stack(Stack** stack) {
    Stack* i = *stack;
    while (i != NULL) {
        Stack* next = i->next;
        free(i->value);
        free(i);
        i = next;
    }
    *stack = NULL;
}

void Stack_push(Stack** stack, char* value) {
    // create new node
    Stack* node = (Stack*)malloc(sizeof(Stack));
    node->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);
    // old first is assigned to node next
    node->next = *stack;
    // new node is added to beginning of list (set as first node)
    *stack = node;
}

// stack: pointer to first node of stack
Stack* Stack_pop(Stack** stack) {
    Stack* node = *stack;
    if (node != NULL) {
        *stack = node->next;
        node->next = NULL;
    }
    return node;
}

void Stack_print(Stack* stack, char* name) {
    printf("%s = (", name);
    for (Stack* i = stack; i != NULL; i = i->next) {
        if (i != stack) {
            printf(", ");
        }
        printf("\"%s\"", i->value);
    }
    printf(")\n");
}

void create_cities_Stack(Stack** cities) {
    create_Stack(cities);
    // add a value to the beginning of the list
    Stack_push(cities, "Moscow");
    // add a value to the beginning of the list
    Stack_push(cities, "San Diego");
    // add a value to the beginning of the list
    Stack_push(cities, "Emerald Hills");
    // add a value to the beginning of the list
    Stack_push(cities, "Keiv");
    // add a value to the beginning of the list
    Stack_push(cities, "Molokai");
    // add a value to the beginning of the list
    Stack_push(cities, "New York");
    // add a value to the beginning of the list
    Stack_push(cities, "Kula");
}

int main(int argc, char** argv) {
    printf("CStack: here.\n");
    // initialize unsorted
    Stack* unsorted;
    create_cities_Stack(&unsorted);
    // print unsorted
    Stack_print(unsorted, "unsorted");
    // pop
    Stack* node = Stack_pop(&unsorted);
    if (node != NULL) {
        free_Stack(&node);
    }
    // print unsorted
    Stack_print(unsorted, "unsorted");
    // free unsprted
    free_Stack(&unsorted);
    return 0; // success (to bash)
}

