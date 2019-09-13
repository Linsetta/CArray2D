#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 3, 2, 1
//       *
// 
// 1, 2, 3

void sorted_array_insert(double* array, int length, double value) {
    // loop to find where to insert value
    for (int j = 0; j < length; j ++) {
        // check to see if j is where we should insert value
        if (value < array[j]) {
            // Move end of sorted_array one place to the right to make room for
            // new element at j.
            //for (int k = length - 1; k >= j; k --) {
            //    array[k + 1] = array[k];
            //}
            memmove(array + j + 1, array + j, sizeof(double) * (length - j)); // see: man memmove
            // put our value in its newly created place
            array[j] = value;
            return;
        }
    }
    // if greater than everything, place at end of array
    array[length] = value;
}

int main () {
    printf ("CArray1DSort: here.\n");
    int input_length = 10;
    // allocate array
    double* input_array = (double*)malloc(sizeof(double) * input_length);
    double* sorted_array = (double*)malloc(sizeof(double) * input_length);
    // initialize array
    for (int i = 0; i < input_length; i ++) {
        double random_number_0_to_1 = ((double)random()) / ((double)RAND_MAX); // see: man random
        double random_number_2_to_5 = random_number_0_to_1 * (5.0 - 2.0) + 2.0;
        input_array[i] = random_number_2_to_5;
    }
    // print input_array
    printf("input_array = (");
    for (int i = 0; i < input_length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%g", input_array[i]);
    }
    printf(")\n");
    // insertion sort input_array into sorted_array
    for (int i = 0; i < input_length; i ++) {
        // insert input_array[i] into sorted_array
        sorted_array_insert(sorted_array, i, input_array[i]);
    }
    // print sorted_array
    printf("sorted_array = (");
    for (int i = 0; i < input_length; i ++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%g", sorted_array[i]);
    }
    printf(")\n");
    // free input_array
    free(input_array);
    // free sorted_array
    free(sorted_array);
    return 0;
}
