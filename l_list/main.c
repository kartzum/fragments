#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

// l_list. Start.

struct l_node {
    int k;
    int s;
    void *data;
    struct l_node *next;
};

struct l_list {
    struct l_node *n;
};

struct l_list *l_list() {
    struct l_list *r = malloc(sizeof(struct l_list));
    r->n = NULL;
    return r;
}

void l_list_add(struct l_list *l, int k, int s, void *data) {
    struct l_node *result = malloc(sizeof(struct l_node));
    result->k = k;
    result->data = malloc(s);
    result->s = s;
    result->next = NULL;

    if (l->n == NULL) {
        l->n = result;
    } else {
        result->next = l->n;
        l->n = result;
    }

    memcpy(result->data, data, s);
}

void l_list_for(struct l_list *l, void (*f)(struct l_node *i)) {
    struct l_node *s = l->n;
    while (s) {
        (*f)(s);
        s = s->next;
    }
}

void l_list_printf_c(int k, int s, void *data) {
    printf("%d, ", k);
    char *d = data;
    for (int i = 0; i < s; i++) {
        printf("%c", d[i]);
    }
    printf("\n");
}

void l_list_printf(struct l_node *n) {
    l_list_printf_c(n->k, n->s, n->data);
}

void l_list_free(struct l_list *l) {
    struct l_node *s = l->n;
    while (s) {
        struct l_node *next = s->next;
        free(s->data);
        free(s);
        s = next;
    }
    free(l);
}

// l_list. Finish.

void l_list_for_test() {
    struct l_list *l = l_list();
    l_list_add(l, 1, 1, "1");
    l_list_add(l, 2, 1, "2");
    l_list_add(l, 3, 1, "3");
    l_list_for(l, l_list_printf);
    l_list_free(l);
}

int main() {
    l_list_for_test();
    return 0;
}