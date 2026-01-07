#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
    t_btree *n1 = bstree_create_node(5);
    t_btree *n2 = bstree_create_node(10);

    printf("Node1: %d\n", n1->item);
    printf("Node2: %d\n", n2->item);

    free(n1);
    free(n2);
    return 0;
}
