#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("CArray1DReverse.main: here.\n");
    int length = 10;
    printf("The length of array is: %d\n", length); 
    // allocate data
    char* data = (char*)malloc(sizeof(char) * length);
    // initialize data
    for (int i = 0; i < length; i ++) {
        data[i] = 'A' + i;
    }
    // print data
    printf("data = {");
    for (int i = 0; i < length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%c", data[i]);
        char* ptr = data + i;
        //char* ptr = &(data[i]);
        printf("(nina: %%p=%p)", ptr);
        printf("(nina: %%c=%c)", *ptr);
    }
    printf("}\n");
    // reverse data
    for (int i = 0; i < (length / 2); i ++) {
        char temp = data[i];
        data[i] = data[length - 1 - i];
        data[length - 1 - i] = temp;
    }
    // print data
    printf("data = {");
    for (int i = 0; i < length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%c", data[i]);
    }
    printf("}\n");
    // free data
    free(data);
    return 0;
}

