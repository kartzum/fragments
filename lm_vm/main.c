#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// l. Start.

// common. Start.

struct l_code {
    int iload; // load an int value from a local variable #index
};

struct l_code l_code() {
    struct l_code result;
    result.iload = 21;
    return result;
};

// common. Finish.

// code. Start.

struct l_s_node {
    int k;
    int v;
};

struct l_s_code {
    struct l_s_node **data;
    int size;
};

struct l_s_code *l_s_code() {
    struct l_s_code *c = calloc(1, sizeof(struct l_s_code));
    c->size = 5;
    return c;
}

void l_s_code_free(struct l_s_code **c) {
    struct l_s_code *c_i = *c;
    struct l_s_node **d = c_i->data;
    if (d != NULL) {
        for (int i = 0; i < c_i->size; i++) {
            if (d[i] != NULL) {
                free(d[i]);
                d[i] = NULL;
            }
        }
    }
    free(*c);
    *c = NULL;
}

struct l_s_node **l_s_code_alloc(struct l_s_code *c) {
    struct l_s_node **d = NULL;
    if (c->data == NULL) {
        d = calloc(1, sizeof(struct l_s_node *) * c->size);
        c->data = d;
    } else {
        d = c->data;
    }
    return d;
}

struct l_s_node **l_s_code_realloc(struct l_s_code *c) {
    struct l_s_node **d = NULL;
    if (c->data == NULL) {
        d = calloc(1, sizeof(struct l_s_node *) * c->size);
        c->data = d;
    } else {
        d = realloc(c->data, sizeof(struct l_s_node *) * c->size);
        c->data = d;
    }
    return d;
}

struct l_s_node **l_s_code_data(struct l_s_code *c, int i) {
    struct l_s_node **d = NULL;
    if (i >= 0) {
        if (i < c->size) {
            d = l_s_code_alloc(c);
        } else if (i < c->size * 2) {
            c->size = c->size * 2;
            d = l_s_code_realloc(c);
        } else {
            c->size = c->size * ((i / c->size) + 1);
            d = l_s_code_realloc(c);
        }
    }
    return d;
}

void l_s_code_set(struct l_s_code *c, int i, int k, int v) {
    struct l_s_node **d = l_s_code_data(c, i);
    struct l_s_node *node = calloc(1, sizeof(struct l_s_node));
    node->k = k;
    node->v = v;
    d[i] = node;
}

struct l_s_node *l_s_code_get_i(struct l_s_code *c, int i) {
    struct l_s_node *result = NULL;
    if (i >= 0 && i < c->size) {
        struct l_s_node **d = c->data;
        if (d != NULL) {
            result = d[i];
        }
    }
    return result;
}

void l_s_code_for(struct l_s_code *c, void (*f)(struct l_s_node *i)) {
    struct l_s_node **d = c->data;
    for (int i = 0; i < c->size; i++) {
        struct l_s_node *v = d[i];
        if (v != NULL) {
            (*f)(d[i]);
        }
    }
}

void l_s_code_printf_c(struct l_s_node *n) {
    printf("%d, %d\n", n->k, n->v);
}

// code. Finish.

// vm. Start.

struct l_vm {
    struct l_s_code *c;
    struct l_code code;
};

struct l_vm *l_vm() {
    struct l_vm *result = calloc(1, sizeof(struct l_vm));
    result->c = l_s_code();
    result->code = l_code();
    return result;
}

void l_vm_free(struct l_vm **v) {
    struct l_vm *v_i = *v;
    l_s_code_free(&v_i->c);
    free(*v);
    *v = NULL;
}

void l_vm_exec(struct l_vm *v) {
    int ip = 0;
    struct l_s_node *s_node = l_s_code_get_i(v->c, ip);

    while (s_node != NULL) {
        if (s_node->k == v->code.iload) {
        }
        ip++;
        s_node = l_s_code_get_i(v->c, ip);
    }
}

// vm. Finish.

// l. Finish.

void l_s_code_test(bool trace) {
    struct l_s_code *c = l_s_code();
    struct l_code code = l_code();
    l_s_code_set(c, 0, code.iload, 0);
    l_s_code_set(c, 1, code.iload, 1);
    if (trace) {
        l_s_code_for(c, l_s_code_printf_c);
    }
    l_s_code_free(&c);
}

void l_vm_test(bool trace) {
    struct l_vm *v = l_vm();
    l_vm_exec(v);
    l_vm_free(&v);
}

void l_test(bool trace) {
    l_s_code_test(trace);
    l_vm_test(trace);
}

int main() {
    bool trace = true;
    l_test(trace);
    return 0;
}