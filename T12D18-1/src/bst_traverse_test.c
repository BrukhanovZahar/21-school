#include <stdio.h>

#include "bst.h"

void applyf(int value) { printf("%d ", value); }

int cmp(int a, int b) { return a - b; }

void s21_btree_infix() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 2, cmp);
    bstree_insert(root, 7, cmp);
    bstree_insert(root, 3, cmp);
    bstree_insert(root, 8, cmp);
    bstree_insert(root, 1, cmp);
    bstree_insert(root, 6, cmp);
    printf("Infix output:\n");
    bstree_apply_infix(root, applyf);
    bstree_destroy(root);
}

void s21_btree_prefix() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 2, cmp);
    bstree_insert(root, 7, cmp);
    bstree_insert(root, 3, cmp);
    bstree_insert(root, 8, cmp);
    bstree_insert(root, 1, cmp);
    bstree_insert(root, 6, cmp);
    printf("Prefix output:\n");
    bstree_apply_prefix(root, applyf);
    bstree_destroy(root);
}

void s21_btree_postfix() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 2, cmp);
    bstree_insert(root, 7, cmp);
    bstree_insert(root, 3, cmp);
    bstree_insert(root, 8, cmp);
    bstree_insert(root, 1, cmp);
    bstree_insert(root, 6, cmp);
    printf("Postfix output:\n");
    bstree_apply_postfix(root, applyf);
    bstree_destroy(root);
}

int main() {
#ifdef Q5
    s21_btree_infix();
    printf("\n");
    s21_btree_prefix();
    printf("\n");
    s21_btree_postfix();
#endif
}