#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

// y_array. Start.

struct y_node {
    int k;
    int s;
    void *data;
};

struct y_array {
    struct y_node **data;
    int size;
};

struct y_array *y_array() {
    struct y_array *result = calloc(1, sizeof(struct y_array));
    result->size = 2;
    return result;
}

struct y_node **y_array_alloc(struct y_array *a) {
    struct y_node **d = NULL;
    if (a->data == NULL) {
        d = calloc(1, sizeof(struct y_node *) * a->size);
        a->data = d;
    } else {
        d = a->data;
    }
    return d;
}

struct y_node **y_array_realloc(struct y_array *a) {
    struct y_node **d = NULL;
    if (a->data == NULL) {
        d = calloc(1, sizeof(struct y_node *) * a->size);
        a->data = d;
    } else {
        d = realloc(a->data, sizeof(struct y_node *) * a->size);
        a->data = d;
    }
    return d;
}

struct y_node **y_array_data(struct y_array *a, int i) {
    struct y_node **d = NULL;
    if (i >= 0) {
        if (i < a->size) {
            d = y_array_alloc(a);
        } else if (i < a->size * 2) {
            a->size = a->size * 2;
            d = y_array_realloc(a);
        } else {
            a->size = a->size * ((i / a->size) + 1);
            d = y_array_realloc(a);
        }
    }
    return d;
}

void y_array_set(struct y_array *a, int i, int k, int s, void *data) {
    struct y_node **d = y_array_data(a, i);
    if (d != NULL) {
        struct y_node *node = calloc(1, sizeof(struct y_node));
        node->data = malloc(s);
        node->s = s;
        node->k = k;
        memcpy(node->data, data, s);
        d[i] = node;
    }
}

void y_array_get(struct y_array *a, int i, void (*f)(struct y_node *i)) {
    if (i >= 0 && i < a->size) {
        struct y_node **d = a->data;
        (*f)(d[i]);
    }
}

void y_array_for(struct y_array *a, void (*f)(struct y_node *i)) {
    struct y_node **d = a->data;
    for (int i = 0; i < a->size; i++) {
        struct y_node *v = d[i];
        if (v != NULL) {
            (*f)(d[i]);
        }
    }
}

void y_array_free(struct y_array *a) {
    struct y_node **d = a->data;
    for (int i = 0; i < a->size; i++) {
        if (d[i] != NULL) {
            free(d[i]->data);
            free(d[i]);
            d[i] = NULL;
        }
    }
}

void y_array_printf_i(int k, int s, void *data) {
    int v = *((int *) data);
    printf("%d, %d\n", k, v);
}

void y_array_printf_n(struct y_node *n) {
    y_array_printf_i(n->k, n->s, n->data);
}

// y_array. Finish.

void y_array_for_test() {
    struct y_array *a = y_array();
    int n = 5;
    for (int i = 0; i < n; i++) {
        y_array_set(a, i, i, sizeof(int), &i);
    }
    y_array_for(a, y_array_printf_n);
    y_array_free(a);
    free(a);
}

void y_array_get_test() {
    struct y_array *a = y_array();
    int i = 10;
    y_array_set(a, 10, 1, sizeof(int), &i);
    y_array_get(a, 10, y_array_printf_n);
    y_array_free(a);
    free(a);
}

int main() {
    y_array_for_test();
    y_array_get_test();
    return 0;
}