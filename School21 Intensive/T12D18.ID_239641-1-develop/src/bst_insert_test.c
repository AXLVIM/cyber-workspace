#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int cmp(int a, int b) { return a - b; }

void print_tree(t_btree *root) {
    if (root) {
        print_tree(root->left);
        printf("%d ", root->item);
        print_tree(root->right);
    }
}

int main() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 3, cmp);
    bstree_insert(root, 8, cmp);

    printf("Tree: ");
    print_tree(root);
    printf("\n");

    free(root->left);
    free(root->right);
    free(root);
    return 0;
}
