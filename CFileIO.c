#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage () {
    printf("CFileIO\n"
           "\n"
           "USAGE\n"
            "\n"
            "    CFileIO <in-file> <out-file>\n"
            "\n");
}

int process_input_to_output(char* in_file_name, char* out_file_name) {
    printf ("Processing input (%s) to output (%s).\n", in_file_name, out_file_name);
    FILE* in_file = fopen (in_file_name, "r");
    if (in_file == NULL) {
        printf("Error opening \"%s\" for reading.\n", in_file_name);
        return -1; // ERROR (non-zero) returned to the operating system shell
    }
    fseek(in_file, 0, SEEK_END);
    long in_file_size = ftell(in_file);
    rewind(in_file);
    char* in_file_contents = (char*)malloc(in_file_size + 1);
    in_file_contents[in_file_size] = '\0';
    fread(in_file_contents, sizeof(char), in_file_size, in_file);
    fclose(in_file);
    {
        int i;
        printf ("1st line> ");
        for (i = 0; in_file_contents[i] != '\0' && in_file_contents[i] != '\n'; i ++) {
            printf ("%c", in_file_contents[i]);
        }
        printf ("\n");
    }

    free(in_file_contents);
    return 0; // SUCCESS (zero) returned to the operating system shell
}

int main (int argc, char** argv) {
    if (argc != 3) {
        printf ("%s: Please give exactly 2 arguments.\n", argv[0]);
        print_usage ();
        return 1; // ERROR (non-zero) returned to the operating system shell
    }
    return process_input_to_output(argv[1], argv[2]);
}

