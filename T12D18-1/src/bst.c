#include "bst.h"

t_btree *bstree_create_node(int item) {
    t_btree *new_node = (t_btree *)malloc(sizeof(t_btree));
    new_node->item = item;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    if (root == NULL) {
        return;
    }
    if (cmpf(item, root->item) < 0) {
        if (root->left == NULL) {
            t_btree *new_node = bstree_create_node(item);
            root->left = new_node;
        } else {
            bstree_insert(root->left, item, cmpf);
        }
    } else {
        if (root->right == NULL) {
            t_btree *new_node = bstree_create_node(item);
            root->right = new_node;
        } else {
            bstree_insert(root->right, item, cmpf);
        }
    }
}

void bstree_destroy(t_btree *root) {
    if (root == NULL) {
        return;
    }
    bstree_destroy(root->left);
    bstree_destroy(root->right);
    free(root);
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_infix(root->left, applyf);
    applyf(root->item);
    bstree_apply_infix(root->right, applyf);
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    applyf(root->item);
    bstree_apply_prefix(root->left, applyf);
    bstree_apply_prefix(root->right, applyf);
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_postfix(root->left, applyf);
    bstree_apply_postfix(root->right, applyf);
    applyf(root->item);
}