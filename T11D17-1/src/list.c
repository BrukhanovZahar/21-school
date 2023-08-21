#include "list.h"

struct node *init(struct door *door) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->door = door;
    new_node->next = NULL;
    return new_node;
}

struct node *add_door(struct node *elem, struct door *door) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->door = door;
    new_node->next = elem->next;
    elem->next = new_node;
    return elem;
}

struct node *find_door(int door_id, struct node *root) {
    struct node *current = root;
    struct node *new_node = NULL;
    while (current != NULL) {
        if (current->door->id == door_id) {
            new_node = current;
            break;
        }
        current = current->next;
    }
    return new_node;
}

struct node *remove_door(struct node *elem, struct node *root) {
    struct node *new_node;
    if (root == elem) {
        new_node = root->next;
        free(root);
    } else {
        struct node *current = root;
        while (current != NULL && current->next != elem) {
            current = current->next;
        }
        if (current != NULL) {
            current->next = elem->next;
            free(elem);
        }
        new_node = root;
    }
    return new_node;
}

void destroy(struct node *root) {
    struct node *current = root;
    while (current != NULL) {
        struct node *next = current->next;
        free(current);
        current = next;
    }
}