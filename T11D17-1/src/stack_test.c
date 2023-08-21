#include "stack.h"

int test_push() {
    int res = 1;
    struct stack *s = init();
    push(s, 1);
    push(s, 2);
    if (s->top->data != 2) {
        res = 0;
    }
    destroy(s);
    return res;
}

int test_pop() {
    int res = 1;
    struct stack *s = init();
    push(s, 1);
    push(s, 2);
    int pop_date = pop(s);
    if (pop_date != 2) {
        res = 0;
    }
    destroy(s);
    return res;
}

int main() {
    int push_res = test_push();
    int pop_res = test_pop();
    if (push_res == 1) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    if (pop_res == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    return 0;
}