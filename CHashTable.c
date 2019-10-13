#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct AssociatedData_s AssociatedData;
struct AssociatedData_s {
    int grade;
    int age;
};

typedef struct HashTableNode_s HashTableNode;
struct HashTableNode_s {
    char*          key;
    AssociatedData associated_data;
    HashTableNode* next;
};

typedef struct HashTable_s HashTable;
struct HashTable_s {
    int             length;
    HashTableNode** array; // pointer to array of linked list node pointers
};

AssociatedData* HashTable_find(HashTable* hash, char* key);

// the most important part of hash table, computes hash value (int) from key
unsigned int key_hash_value(char* key) {
    int key_length = strlen(key);
    unsigned int hash_value = 0;
    for (int i = 0; i < key_length; i ++) {
        hash_value += key[i] * key[i] * key[i];
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
            free(node->key);
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
                printf("%s (hash_value=%u) [grade=%d, age=%d]",
                       node->key,
                       key_hash_value(node->key),
                       node->associated_data.grade,
                       node->associated_data.age);
                index ++;
            }
            printf("]\n");
        }
    }
}

HashTableNode* HashTable_insert(HashTable* hash, char* key, AssociatedData* associated_data) {
    HashTableNode* new_node = NULL;
    if (! HashTable_find(hash, key)) {
        unsigned int   hash_value = key_hash_value(key);
        unsigned int   index      = hash_value % hash->length;
        new_node                  = (HashTableNode*)malloc(sizeof(HashTableNode));
        new_node->key             = (char*)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_node->key, key);
        memcpy(&(new_node->associated_data), associated_data, sizeof(AssociatedData));
        // insert new node at beginning of linked list (hash->array[index])
        new_node->next     = hash->array[index];
        hash->array[index] = new_node;
    } else {
        printf("HashTable_insert: found duplicate key!  (%s)\n", key);
    }
    return new_node;
}

int HashTable_remove(HashTable* hash, char* key) {
    // the magic of hash table computes array index from key hash value
    unsigned int   hash_value = key_hash_value(key);
    unsigned int   index      = hash_value % hash->length;
    // remove all keys from singly linked list
    HashTableNode* previous   = NULL;
    HashTableNode* node       = hash->array[index]; // this is first node of singly linked list
    int            count      = 0;
    while (node != NULL) {
        HashTableNode* next = node->next;
        if (strcmp(node->key, key) == 0) {
            if (previous == NULL) {
                hash->array[index] = next;
            } else {
                previous->next = next;
            }
            free(node->key);
            free(node);
            count ++;
        } else {
            previous = node;
        }
        node = next;
    }
    return count;
}

AssociatedData* HashTable_find(HashTable* hash, char* key) {
    unsigned int   hash_value = key_hash_value(key);
    unsigned int   index      = hash_value % hash->length;
    HashTableNode* node       = hash->array[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return &(node->associated_data); // found
        }
        node = node->next;
    }
    return NULL; // not found
}

int HashTable_count(HashTable* hash, char* key) {
    unsigned int   hash_value = key_hash_value(key);
    unsigned int   index      = hash_value % hash->length;
    int            count      = 0;
    HashTableNode* node       = hash->array[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
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
    AssociatedData associated_data;
    associated_data.grade = 5;
    associated_data.age = 10;
    HashTable_insert(hash, "Nina", &associated_data);
    HashTable_insert(hash, "Nina", &associated_data);
    HashTable_insert(hash, "nina", &associated_data);
    HashTable_insert(hash, "nina", &associated_data);
    associated_data.grade = 9;
    associated_data.age = 14;
    HashTable_insert(hash, "Bo", &associated_data);
    HashTable_insert(hash, "Morgan", &associated_data);
    HashTable_insert(hash, "morgan", &associated_data);
    HashTable_insert(hash, "morgan", &associated_data);
    HashTable_insert(hash, "Elena", &associated_data);
    HashTable_remove(hash, "Bo");
    HashTable_remove(hash, "Morgan");
    HashTable_remove(hash, "morgan");
    printf("---\n");
    print_HashTable(hash);
    printf("---\n");
    AssociatedData* nina_associated_data = HashTable_find(hash, "Nina");
    if (nina_associated_data != NULL) {
        printf("Found Nina %d time(s)!\n", HashTable_count(hash, "Nina"));
        printf("  nina.grade = %d\n", nina_associated_data->grade);
        printf("  nina.age = %d\n", nina_associated_data->age);
    } else {
        printf("Did not find Nina!\n");
    }
    printf("---\n");
    AssociatedData* elena_associated_data = HashTable_find(hash, "Elena");
    if (elena_associated_data != NULL) {
        printf("Found Elena %d time(s)!\n", HashTable_count(hash, "Elena"));
        printf("  elena.grade = %d\n", elena_associated_data->grade);
        printf("  elena.age = %d\n", elena_associated_data->age);
    } else {
        printf("Did not find Elena!\n");
    }
    free_HashTable(hash);
    return 0; // success (to bash)
}

