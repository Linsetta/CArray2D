#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USER_INPUT_SIZE 32

void print_user_input(char* user_input) {
    int i;
    printf("user_input = [");
    for (i = 0; i < USER_INPUT_SIZE; i ++) {
        if (i != 0) {
            printf(", ");
        }
        if (user_input[i] == '\0') {
            printf("'\\0'");
        } else if (user_input[i] == '\n') {
            printf("'\\n'");
        } else {
            printf("'%c'", user_input[i]);
        }
    }
    printf("]\n");
}

void test_strtok() {
    char user_input[USER_INPUT_SIZE];
    print_user_input(user_input);
    printf("User, enter a string: ");
    fgets(user_input, USER_INPUT_SIZE - 1, stdin);
    printf("Thanks a lot, user!  I agree that %s\n", user_input);
    print_user_input(user_input);
    char* token = strtok(user_input, " ");
    while (token != NULL) {
        print_user_input(user_input);
        printf("The current token is \"%s\".\n", token);
        token = strtok(NULL, " ");
        sleep(1);
    }
    print_user_input(user_input);
}

void test_strpbrk() {
    char user_input[USER_INPUT_SIZE];
    printf("User, enter a string: ");
    fgets(user_input, USER_INPUT_SIZE - 1, stdin);
    printf("Thanks a lot, user!  I agree that %s\n", user_input);
    print_user_input(user_input);
    char* p = user_input;
    do {
        p = strpbrk(p, "()[]{},.<>/\\~!@#$%^&*_+|");
        if (p == NULL) {
            printf("Could not find acceptible character.\n");
        } else {
            printf("Found acceptible character at this point: %s\n", p);
            p ++;
        }
        sleep(1);
    } while (p != NULL);
}

void test_strstr() {
    char user_input[USER_INPUT_SIZE];
    printf("User, enter a string: ");
    fgets(user_input, USER_INPUT_SIZE - 1, stdin);
    printf("Thanks a lot, user!  I agree that %s\n", user_input);
    print_user_input(user_input);
    char* needle = "sky";
    char* str = user_input;
    do {
        str = strstr(str, needle);
        if (str == NULL) {
            printf("I have failed in my quest to find the %s.\n", needle);
        } else {
            printf("I found the %s right here ---> %s\n", needle, str);
            str += strlen(needle);
        }
        sleep(1);
    } while (str != NULL);
}

int main (int argc, char** argv) {
    //test_strtok();
    //test_strpbrk();
    test_strstr();
    return 0;
}

