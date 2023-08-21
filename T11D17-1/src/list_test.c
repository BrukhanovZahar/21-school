#include "list.h"

int test_add_door() {
    int res = 1;
    struct door door1 = {1, 0};
    struct door door2 = {2, 1};
    struct node *root = init(&door1);
    root = add_door(root, &door2);
    if (root->next == NULL || root->next->door->id != 2) {
        res = 0;
    }
    destroy(root);
    return res;
}

int test_remove_door() {
    int res = 1;
    struct door door1 = {1, 0};
    struct door door2 = {2, 1};
    struct door door3 = {3, 0};
    struct node *root = init(&door1);
    struct node *first = root;
    root = add_door(root, &door2);
    root = add_door(root->next, &door3);
    root = find_door(1, first);
    root = remove_door(root->next, root);
    if (root->next == NULL || root->next->door->id != 3) {
        res = 0;
    }
    destroy(root);
    return res;
}

int main() {
    int add_door_res = test_add_door();
    int remove_door_res = test_remove_door();
    if (add_door_res == 1) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    if (remove_door_res == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    return 0;
}