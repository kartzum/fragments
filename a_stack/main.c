#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

// a_stack. Start.

struct a_node {
    int k;
    int s;
    void *data;
};

struct a_stack {
    struct a_node **data;
    int size;
    int top;
};

struct a_stack *a_stack() {
    struct a_stack *result = malloc(sizeof(struct a_stack));
    result->size = 10;
    result->top = -1;
    result->data = NULL;
    return result;
}

void a_stack_push(struct a_stack *a, int k, int s, void *data) {
    if (a->top + 1 >= a->size) {
        return;
    }

    a->top++;

    struct a_node **d;
    if (a->data == NULL) {
        d = malloc(sizeof(struct a_node *) * a->size);
        a->data = d;
    } else {
        d = a->data;
    }

    struct a_node *node = malloc(sizeof(struct a_node));
    node->data = malloc(s);
    node->s = s;
    node->k = k;
    memcpy(node->data, data, s);

    d[a->top] = node;
}

void a_stack_pop(struct a_stack *a, void (*f)(struct a_node *i)) {
    if (a->top >= 0) {
        struct a_node **d = a->data;
        struct a_node *node = d[a->top];

        (*f)(node);

        free(node->data);
        free(node);
        d[a->top] = NULL;

        a->top--;
    }
}

void a_stack_for(struct a_stack *a, void (*f)(struct a_node *i)) {
    struct a_node **d = a->data;
    int i = a->top;
    while (i >= 0) {
        struct a_node *node = d[i];
        if (node != NULL) {
            (*f)(node);
        }
        i--;
    }
}

void a_stack_printf_c(int k, int s, void *data) {
    printf("%d, ", k);
    char *d = data;
    for (int i = 0; i < s; i++) {
        printf("%c", d[i]);
    }
    printf("\n");
}

void a_stack_printf(struct a_node *n) {
    a_stack_printf_c(n->k, n->s, n->data);
}

void a_stack_free(struct a_stack *a) {
    struct a_node **d = a->data;
    int i = a->top;
    while (i >= 0) {
        struct a_node *node = d[i];
        if (node != NULL) {
            free(node->data);
            free(node);
            d[i] = NULL;
        }
        i--;
    }
}

// a_stack. Finish.

void a_stack_borders_test() {
    char *p[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "1"};
    int n = 11;
    struct a_stack *a = a_stack();
    for (int i = 0; i < n; i++) {
        a_stack_push(a, i, 1, p[i]);
    }
    a_stack_for(a, a_stack_printf);
    for (int j = 0; j < n; j++) {
        a_stack_pop(a, a_stack_printf);
    }
    a_stack_for(a, a_stack_printf);
    a_stack_free(a);
    free(a);
}

void a_stack_free_test() {
    struct a_stack *a = a_stack();
    a_stack_push(a, 1, 1, "1");
    a_stack_push(a, 2, 1, "2");
    a_stack_for(a, a_stack_printf);
    a_stack_free(a);
    free(a);
}

int main() {
    a_stack_borders_test();
    a_stack_free_test();
    return 0;
}