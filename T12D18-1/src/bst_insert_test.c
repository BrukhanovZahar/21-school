#include <stdio.h>

#include "bst.h"

int cmp(int a, int b) { return a - b; }

void test_bstree_insert_node() {
    t_btree *node = bstree_create_node(1);
    printf("The first vertex 1\n");
    printf("Adding Vertex 3:\n");
    bstree_insert(node, 3, cmp);
    if (node->right->item == 3 && node->left == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n");
    printf("Adding Vertex 0:\n");
    bstree_insert(node, 0, cmp);
    if (node->right->item == 3 && node->left->item == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n");
    printf("Adding Vertex 2:\n");
    bstree_insert(node, 2, cmp);
    if (node->right->item == 3 && node->left->item == 0 && node->right->left->item == 2) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    free(node->right->left);
    free(node->right);
    free(node->left);
    free(node);
}

int main() {
#ifdef Q4
    test_bstree_insert_node();
#endif
}