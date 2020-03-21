#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** create_jagged_array(int height) {
    int** table = (int**)malloc(sizeof(int*) * (height + 1));
    int i, j;
    table[0] = (int*)(unsigned long)height;
    for (i = 0; i < height; i ++) {
        int len = rand() % 5 + 2;
        table[i + 1] = (int*)malloc(sizeof(int) * (len + 1));
        table[i + 1][0] = len;
        for (j = 0; j < len; j ++) {
            table[i + 1][j + 1] = 11;
        }
    }
    return table;
}

void free_jagged_array(int** table) {
    int height = (int)(unsigned long)table[0];
    int i;
    for (i = 0; i < height; i ++) {
        free (table[i + 1]);
    }
    free (table);
}

void print_jagged_array(int** table) {
    int height = (int)(unsigned long)table[0];
    int i, j;
    printf ("table = 0x%016lX, sizeof(table) = %d\n", (unsigned long)table, (int)sizeof(table));
    for (i = -1; i < height; i ++) {
        printf ("table[%d] = 0x%016lX, sizeof(table[%d]) = %d\n", i + 1, (unsigned long)table[i + 1], i, (int)sizeof(table[i + 1]));
        if (i != -1) {
            for (j = 0; j < table[i + 1][0] + 1; j ++) {
                printf ("table[%d][%d] = 0x%08X, sizeof(table[%d][%d]) = %d\n", i + 1, j, table[i + 1][j], i + 1, j, (int)sizeof(table[i + 1][j]));
            }
        }
    }
    
}

int main (int argc, char** argv) {
    printf ("CArray2DJagged: here.\n");
    
    int** table = create_jagged_array(4);
    table[4][2] = 13;
    print_jagged_array(table);
    
    int** pWalk;
    pWalk = table + 3;
    pWalk ++;
    printf ("pWalk = 0x%016lX, sizeof(pWalk) = %d\n", (unsigned long)pWalk, (int)sizeof(pWalk));
    printf ("*pWalk = 0x%016lX, sizeof(*pWalk) = %d\n", (unsigned long)*pWalk, (int)sizeof(*pWalk));
    printf ("pWalk[0] = 0x%016lX, sizeof(pWalk[0]) = %d\n", (unsigned long)pWalk[0], (int)sizeof(pWalk[0]));
    printf ("(*pWalk)[2] = 0x%016lX, sizeof((*pWalk)[2]) = %d\n", (unsigned long)(*pWalk)[2], (int)sizeof((*pWalk)[2]));
    
    free_jagged_array(table);
    
    return 0;
}

