#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char  state[3];
    int   year;
    char *city;
} CITY;

typedef struct nodeTag {
    CITY            city;
    struct nodeTag *next;
} NODE;

void NODE_print(NODE* node, int depth) {
    printf("NODE {\n");
    for (int i = 0; i < depth; i ++) {
        printf(" ");
    }
    printf("    city = %s, %s, %d\n", node->city.city, node->city.state, node->city.year);
    for (int i = 0; i < depth; i ++) {
        printf(" ");
    }
    printf("    next = ");
    if (node->next == NULL) {
        printf("NULL\n");
    } else {
        NODE_print(node->next, depth + 11);
    }
    for (int i = 0; i < depth; i ++) {
        printf(" ");
    }
    printf("}\n");
}

void use_the_city_and_node_structs() {
    printf("Using the CITY and NODE structs.\n");
    CITY  city;
    CITY *cityPointer;
    NODE  node1;
    NODE *node1Pointer;
    NODE  node2;
    NODE *node2Pointer;
    NODE  node3;
    NODE *node3Pointer;
    city.state[0] = 'C';
    city.state[1] = 'A';
    city.state[2] = '\0';
    city.year     = 1776;
    city.city     = "Plymouth";
    printf("city = %s, %s, %d\n", city.city, city.state, city.year);
    cityPointer = &city;
    cityPointer->state[0] = 'N';
    cityPointer->state[1] = 'J';
    cityPointer->state[2] = '\0';
    cityPointer->year = 2016;
    cityPointer->city = "Emerald Hills";
    printf("city = %s, %s, %d\n", city.city, city.state, city.year);
    node1.city.state[0] = 'M';
    node1.city.state[1] = 'A';
    node1.city.state[2] = '\0';
    node1.city.year     = 1805;
    node1.city.city     = "Boston";
    node1.next          = NULL;
    node1Pointer = &node1;
    node1Pointer->city.city = "Woweeton";
    node2.city.state[0] = 'L';
    node2.city.state[1] = 'A';
    node2.city.state[2] = '\0';
    node2.city.year     = 1300;
    node2.city.city     = "Wind Hill";
    node2.next          = &node1;
    node2Pointer = &node2;
    node2Pointer->city.city = "Tylonga";
    node3.city.state[0] = 'C';
    node3.city.state[1] = 'A';
    node3.city.state[2] = '\0';
    node3.city.year     = 1997;
    node3.city.city     = "San Diego";
    node3.next          = &node2;
    node3Pointer = &node3;
    node3Pointer->city.year = 2001;
    printf("[\"");
    int index = 0;
    for (NODE* i = &node3; i != NULL; i = i->next) {
        if (index != 0) {
             printf("\", \"");
        }
        printf("%s, %s, %d",
               i->city.city,
               i->city.state,
               i->city.year);
        index ++;
    }
    printf("\"]\n");
    printf("node1 = "); NODE_print(&node1, 0);
    printf("node2 = "); NODE_print(&node2, 0);
    printf("node3 = "); NODE_print(&node3, 0);
    node1.city.city = "Poop Town";
    printf("node1 = "); NODE_print(&node1, 0);
    printf("node2 = "); NODE_print(&node2, 0);
    printf("node3 = "); NODE_print(&node3, 0);
}

void show_simple_tests() {
    int length = 10;
    // allocate a
    char* a = (char*)malloc(sizeof(char) * length);
    // allocate b
    int* b = (int*)malloc(sizeof(int) * length);
    // allocate c
    int* c = (int*)malloc(sizeof(int) * length);
    // allocate d
    char* d = (char*)malloc(sizeof(char) * length);
    // initialize 'a' with indices
    for (int i = 0; i < length; i ++) {
        a[i] = 'A' + i;
    }
    // initialize 'b' with pointers
    for (int* i = b; i != b + length; i ++) {
        *i = 100;
    }
    // copy 'b' to 'c' (c = b)
    memcpy(c, b, sizeof(int) * length);
    // print a
    printf("a = {");
    for (int i = 0; i < length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%c", a[i]);
    }
    printf("}\n");
    printf("reverse a with indices (swap in place)\n");
    for (int i = 0; i < (length / 2); i ++) {
        char temp = a[i];
        a[i] = a[length - 1 - i];
        a[length - 1 - i] = temp;
    }
    // print a with indices
    printf("a = {");
    for (int i = 0; i < length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%c", a[i]);
    }
    printf("}\n");
    printf("copy reverse of 'a' to 'd' with pointers\n");
    {
        char* i = a;
        char* j = d + length - 1;
        while (i != a + length) {
            *j = *i;
            i ++;
            j --;
        }
    }
    // print d with pointers
    printf("d = {");
    for (char* i = d; i != d + length; i ++) {
        if (i != d) {
            printf(", ");
        }
        printf("%c", *i);
    }
    printf("}\n");
    // compare 'a' and 'd'
    {
        int result = memcmp(a, d, sizeof(char) * length);
        if (result == 0) {
            printf("a equals d\n");
        } else if (result < 0) {
            printf("a is less than d\n");
        } else { // result > 0
            printf("a is greater than d\n");
        }
    }
    // print b with pointers
    printf("b = {");
    for (int* i = b; i != b + length; i ++) {
        if (i != b) {
            printf(", ");
        }
        printf("%i", *i);
    }
    printf("}\n");
    // print c with pointers
    printf("c = {");
    for (int* i = c; i != c + length; i ++) {
        if (i != c) {
            printf(", ");
        }
        printf("%i", *i);
    }
    printf("}\n");
    // free 'a'
    free(a);
    // free 'b'
    free(b);
    // free 'c'
    free(c);
    // free 'd'
    free(d);
}

int main(int argc, char** argv) {
    printf("CArray1DPointersAndIndices.main: here.\n");
    //show_simple_tests();
    use_the_city_and_node_structs();
    return 0;
}

