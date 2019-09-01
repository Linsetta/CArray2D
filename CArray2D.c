#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct CArray2D_s {
    int    height;
    int    width;
    char** data;
} CArray2D;

CArray2D* new_CArray2D(int width, int height) {
    CArray2D* c2d = (CArray2D*)malloc(sizeof(CArray2D));
    c2d->width = width;
    c2d->height = height;
    c2d->data = (char**)malloc(sizeof(char*) * height);
    for (int row = 0; row < height; row ++) {
        c2d->data[row] = (char*)malloc(sizeof(char) * width);
        for (int col = 0; col < width; col ++) {
            c2d->data[row][col] = ' ';
        }
    }
    return c2d;
}

char get_CArray2D(CArray2D* c2d, int col, int row) {
    if (row < 0 ||
        col < 0 ||
        row >= c2d->height ||
        col >= c2d->width) {
       printf("get_CArray2D ERROR: row or col out of bounds.\n");
       return 0; 
    }
    return c2d->data[row][col];
}

void set_CArray2D(CArray2D* c2d, int col, int row, char ch) {
    if (row < 0 ||
        col < 0 ||
        row >= c2d->height ||
        col >= c2d->width) {
       printf("set_CArray2D ERROR: row or col out of bounds.\n");
       return; 
    }
    c2d->data[row][col] = ch;
}

void print_CArray2D(CArray2D* c2d) {
    for (int row = 0; row < c2d->height; row ++) {
        for (int col = 0; col < c2d->width; col ++) {
            printf("%c", get_CArray2D(c2d, col, row));
        }
        printf("\n");
    }
}

void free_CArray2D(CArray2D* c2d) {
    for (int row = 0; row < c2d->height; row ++) {
        free(c2d->data[row]);
    }
    free(c2d->data);
    free(c2d);
}

void clear_CArray2D(CArray2D* c2d, char ch) {
    for (int row = 0; row < c2d->height; row ++) {
        for (int col = 0; col < c2d->width; col ++) {
            set_CArray2D(c2d, col, row, ch);
        }
    }
}

int main(int argc, char** argv) {
    printf("CArray2D.main: here.\n");
    CArray2D* c2d = new_CArray2D(24, 6);
    clear_CArray2D(c2d, '~');
    set_CArray2D(c2d, 11, 2, '@');
    print_CArray2D(c2d);
    free_CArray2D(c2d);
    return 0; // success
}

