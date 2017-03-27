#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

// d_list. Start.

struct d_node {
    int k;
    int s;
    void *data;
    struct d_node *next;
    struct d_node *prev;
};

struct d_list {
    struct d_node *head;
    struct d_node *tail;
};

struct d_list *d_list() {
    struct d_list *result = malloc(sizeof(struct d_list));
    result->head = NULL;
    result->tail = NULL;
    return result;
}

void d_list_add(struct d_list *l, int k, int s, void *data) {
    struct d_node *node = malloc(sizeof(struct d_node));
    node->k = k;
    node->s = s;
    node->data = malloc(s);
    memcpy(node->data, data, s);

    node->next = l->head;
    node->prev = NULL;

    if (l->head) {
        l->head->prev = node;
    }
    l->head = node;

    if (l->tail == NULL) {
        l->tail = node;
    }
}

void d_list_for(struct d_list *l, void (*f)(struct d_node *i)) {
    struct d_node *s = l->head;
    while (s) {
        (*f)(s);
        s = s->next;
    }
}

void d_list_printf_c(int k, int s, void *data) {
    printf("%d, ", k);
    char *d = data;
    for (int i = 0; i < s; i++) {
        printf("%c", d[i]);
    }
    printf("\n");
}

void d_list_printf(struct d_node *n) {
    d_list_printf_c(n->k, n->s, n->data);
}

void d_list_free(struct d_list *l) {
    struct d_node *s = l->head;
    while (s) {
        struct d_node *next = s->next;
        free(s->data);
        free(s);
        s = next;
    }
}

// d_list. Finish.

void d_list_for_test() {
    struct d_list *l = d_list();
    d_list_add(l, 1, 1, "1");
    d_list_add(l, 2, 1, "2");
    d_list_add(l, 3, 1, "3");
    d_list_for(l, d_list_printf);
    d_list_free(l);
    free(l);
}

int main() {
    d_list_for_test();
    return 0;
}