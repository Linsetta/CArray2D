#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("CArray2DSimple.main: here.\n");
    int width = 10;
    int height = 3;
    // allocate data
    char** data = (char**)malloc(sizeof(char*) * height);
    // fill data
    for (int row = 0; row < height; row ++) {
        data[row] = (char*)malloc(sizeof(char) * width);
        for (int col = 0; col < width; col ++) {
            data[row][col] = '~';
        }
    }
    // set data
    data[1][1] = '@';
    // print data
    for (int row = 0; row < height; row ++) {
        for (int col = 0; col < width; col ++) {
            printf("%c", data[row][col]);
        }
        printf("\n");
    }
    // free data
    for (int row = 0; row < height; row ++) {
        free(data[row]);
    }
    free(data);
    return 0;
}

