#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("CArray1DPointersAndIndices.main: here.\n");
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
    return 0;
}

