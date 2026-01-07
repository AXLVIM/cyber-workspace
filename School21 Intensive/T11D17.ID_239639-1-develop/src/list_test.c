#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int test_add_door();
int test_remove_door();
int test_find_door();

int main() {
    printf("[add_door] %s\n", test_add_door() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("[remove_door] %s\n", test_remove_door() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("[find_door] %s\n", test_find_door() == SUCCESS ? "SUCCESS" : "FAIL");
    return 0;
}

int test_add_door() {
    struct door d1 = {1, 0}, d2 = {2, 1};
    struct node* root = init(&d1);
    if (!root) return FAIL;

    const struct node* n2 = add_door(root, &d2);
    if (!n2 || root->next != n2) {
        destroy(root);
        return FAIL;
    }

    if (n2->door.id != 2 || n2->door.status != 1) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int test_remove_door() {
    struct door d1 = {1, 0}, d2 = {2, 1}, d3 = {3, 0};
    struct node* root = init(&d1);
    if (!root) return FAIL;

    struct node* n2 = add_door(root, &d2);
    struct node* n3 = add_door(n2, &d3);

    if (!n2 || !n3) {
        destroy(root);
        return FAIL;
    }

    struct node* r1 = remove_door(n2, root);
    if (!r1 || r1 != root || root->next != n3) {
        destroy(r1);
        return FAIL;
    }

    struct node* r2 = remove_door(root, r1);
    if (!r2 || r2 != n3) {
        destroy(r2);
        return FAIL;
    }

    struct node* r3 = remove_door(n3, r2);
    if (r3 != NULL) {
        destroy(r3);
        return FAIL;
    }

    return SUCCESS;
}

int test_find_door() {
    struct door d1 = {1, 0}, d2 = {2, 1}, d3 = {3, 0};
    struct node* root = init(&d1);
    if (!root) return FAIL;

    add_door(root, &d2);
    add_door(root, &d3);

    const struct node* found = find_door(2, root);
    if (!found || found->door.id != 2 || found->door.status != 1) {
        destroy(root);
        return FAIL;
    }

    const struct node* not_found = find_door(999, root);
    if (not_found != NULL) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}