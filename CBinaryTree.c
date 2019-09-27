#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode_s {
    char* data;
    struct BinaryTreeNode_s* left;
    struct BinaryTreeNode_s* right;
} BinaryTreeNode;

BinaryTreeNode* new_binary_tree_node(char* data) {
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(node->data, data);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// recursively frees all children in tree
void free_binary_tree_node(BinaryTreeNode* node) {
    if (node->left != NULL) {
        free_binary_tree_node(node->left);
    }
    if (node->right != NULL) {
        free_binary_tree_node(node->right);
    }
    free(node->data);
    free(node);
}

void print_binary_tree_node_helper(BinaryTreeNode* node) {
    printf("(");
    if (node->left == NULL) {
        printf(".");
    } else {
        print_binary_tree_node_helper(node->left);
    }
    printf(" %s ", node->data);
    if (node->right == NULL) {
        printf(".");
    } else {
        print_binary_tree_node_helper(node->right);
    }
    printf(")");
}

void print_binary_tree_node(BinaryTreeNode* node) {
    print_binary_tree_node_helper(node);
    printf("\n");
}

void insert_sorted_binary_tree_node(BinaryTreeNode* root, BinaryTreeNode* node) {
    int result = strcmp(root->data, node->data);
    if (result > 0) {
        if (root->left == NULL) {
            root->left = node;
        } else {
            insert_sorted_binary_tree_node(root->left, node);
        }
    } else {
        if (root->right == NULL) {
            root->right = node;
        } else {
            insert_sorted_binary_tree_node(root->right, node);
        }
    }
}

int main(int argc, char** argv) {
    printf("CBinaryTree: here.\n");
    BinaryTreeNode* root = new_binary_tree_node("Sun");
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Mercury"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Venus"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Earth"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Mars"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Jupiter"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Saturn"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Uranus"));
    insert_sorted_binary_tree_node(root, new_binary_tree_node("Pluto"));
    print_binary_tree_node(root);
    free_binary_tree_node(root);
    return 0; // success
}

