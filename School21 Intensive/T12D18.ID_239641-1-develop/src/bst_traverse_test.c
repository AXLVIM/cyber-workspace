#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int cmp(int a, int b) { return a - b; }

void apply(int item) { printf("%d ", item); }

int main() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 2, cmp);
    bstree_insert(root, 8, cmp);

    printf("Infix: ");
    bstree_apply_infix(root, apply);
    printf("\n");

    printf("Prefix: ");
    bstree_apply_prefix(root, apply);
    printf("\n");

    printf("Postfix: ");
    bstree_apply_postfix(root, apply);
    printf("\n");

    free(root->left);
    free(root->right);
    free(root);
    return 0;
}
