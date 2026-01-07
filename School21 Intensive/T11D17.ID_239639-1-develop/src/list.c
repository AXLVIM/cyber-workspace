#include "list.h"

#include <stdlib.h>

struct node* init(const struct door* door) {
    if (!door) return NULL;

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node) {
        new_node->door = *door;
        new_node->next = NULL;
    }
    return new_node;
}

struct node* add_door(struct node* elem, const struct door* door) {
    if (!elem || !door) return NULL;

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node) {
        new_node->door = *door;
        new_node->next = elem->next;
        elem->next = new_node;
    }
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current) {
        if (current->door.id == door_id) return current;
        current = current->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (!elem || !root) return root;

    if (elem == root) {
        struct node* next = root->next;
        free(root);
        return next;
    }

    struct node* prev = root;
    while (prev->next && prev->next != elem) {
        prev = prev->next;
    }

    if (prev->next == elem) {
        prev->next = elem->next;
        free(elem);
    }

    return root;
}

void destroy(struct node* root) {
    while (root) {
        struct node* next = root->next;
        free(root);
        root = next;
    }
}