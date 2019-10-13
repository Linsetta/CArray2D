#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct HashTableNode_s HashTableNode;
struct HashTableNode_s {
    char*          data;
    HashTableNode* next;
};

typedef struct HashTable_s HashTable;
struct HashTable_s {
    int             length;
    HashTableNode** array; // pointer to array of linked list node pointers
};

unsigned int data_hash_value(char* data) {
    int data_length = strlen(data);
    unsigned int hash_value = 0;
    for (int i = 0; i < data_length; i ++) {
        hash_value += data[i] * data[i] * data[i];
    }
    return hash_value;
}

// places '*' is used:
// - multiply
// - dereference
// - pointer type definition

HashTable* new_HashTable(int length) {
    HashTable* hash = (HashTable*)malloc(sizeof(HashTable));
    hash->length = length;
    // allocate array of linked lists
    hash->array  = (HashTableNode**)malloc(sizeof(HashTableNode*) * hash->length);
    //for (int i = 0; i < hash->length; i ++) {
    //    hash->array[i] = NULL;
    //}
    memset(hash->array, 0, sizeof(HashTableNode*) * hash->length);
    return hash;
}

void free_HashTable(HashTable* hash) {
    for (int i = 0; i < hash->length; i ++) {
        HashTableNode* node = hash->array[i];
        while (node != NULL) {
            HashTableNode* next = node->next;
            free(node->data);
            free(node);
            node = next;
        }
    }
    free(hash->array);
    free(hash);
}

void print_HashTable(HashTable* hash) {
    for (int i = 0; i < hash->length; i ++) {
        if (hash->array[i] != NULL) {
            printf("array[%d] = [", i);
            int index = 0;
            for (HashTableNode* node = hash->array[i]; node != NULL; node = node->next) {
                if (index != 0) {
                    printf(", ");
                }
                printf("%s (%u)", node->data, data_hash_value(node->data));
                index ++;
            }
            printf("]\n");
        }
    }
}

void HashTable_insert(HashTable* hash, char* data) {
    unsigned int   hash_value = data_hash_value(data);
    unsigned int   index      = hash_value % hash->length;
    HashTableNode* new_node   = (HashTableNode*)malloc(sizeof(HashTableNode));
    new_node->data            = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(new_node->data, data);
    // insert new node at beginning of linked list (hash->array[index])
    new_node->next     = hash->array[index];
    hash->array[index] = new_node;
}

int HashTable_find(HashTable* hash, char* data) {
    unsigned int   hash_value = data_hash_value(data);
    unsigned int   index      = hash_value % hash->length;
    HashTableNode* node       = hash->array[index];
    while (node != NULL) {
        if (strcmp(node->data, data) == 0) {
            return 1; // found
        }
        node = node->next;
    }
    return 0; // not found
}

int HashTable_count(HashTable* hash, char* data) {
    unsigned int   hash_value = data_hash_value(data);
    unsigned int   index      = hash_value % hash->length;
    int            count      = 0;
    HashTableNode* node       = hash->array[index];
    while (node != NULL) {
        if (strcmp(node->data, data) == 0) {
            count ++;
        }
        node = node->next;
    }
    return count;
}


int main(int argc, char** argv) {
    printf("CHashTable: here.\n");
    HashTable* hash = new_HashTable(1000);
    printf("---\n");
    print_HashTable(hash);
    HashTable_insert(hash, "Nina");
    HashTable_insert(hash, "Nina");
    HashTable_insert(hash, "nina");
    HashTable_insert(hash, "nina");
    HashTable_insert(hash, "Bo");
    HashTable_insert(hash, "Morgan");
    HashTable_insert(hash, "morgan");
    HashTable_insert(hash, "morgan");
    printf("---\n");
    print_HashTable(hash);
    printf("---\n");
    if (HashTable_find(hash, "Nina")) {
        printf("Found Nina %d time(s)!\n", HashTable_count(hash, "Nina"));
    } else {
        printf("Did not find Nina!\n");
    }
    printf("---\n");
    if (HashTable_find(hash, "Elena")) {
        printf("Found Elena %d time(s)!\n", HashTable_count(hash, "Elena"));
    } else {
        printf("Did not find Elena!\n");
    }
    free_HashTable(hash);
    return 0; // success (to bash)
}

