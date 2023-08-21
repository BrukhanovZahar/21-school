#include <stdio.h>

#include "bst.h"

void test_bstree_create_node() {
    t_btree *node1 = bstree_create_node(10);
    printf("Creating a new vertex with a value of 10:\n");
    if (node1->item == 10 && node1->left == NULL && node1->right == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n");
    t_btree *node2 = bstree_create_node(-10);
    printf("Creating a new vertex with a value of -10:\n");
    if (node2->item == -10 && node2->left == NULL && node2->right == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    free(node1);
    free(node2);
}

int main() {
#ifdef Q3
    test_bstree_create_node();
#endif
}