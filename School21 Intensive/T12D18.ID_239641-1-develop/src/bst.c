#include "bst.h"

#include <stdlib.h>

t_btree *bstree_create_node(int item) {
    t_btree *node = malloc(sizeof(t_btree));
    if (!node) return NULL;

    node->item = item;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    if (!root) return;

    if (cmpf(item, root->item) < 0) {
        if (root->left) {
            bstree_insert(root->left, item, cmpf);
        } else {
            root->left = bstree_create_node(item);
        }
    } else {
        if (root->right) {
            bstree_insert(root->right, item, cmpf);
        } else {
            root->right = bstree_create_node(item);
        }
    }
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        bstree_apply_infix(root->left, applyf);
        applyf(root->item);
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        applyf(root->item);
        bstree_apply_prefix(root->left, applyf);
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        bstree_apply_postfix(root->left, applyf);
        bstree_apply_postfix(root->right, applyf);
        applyf(root->item);
    }
}
