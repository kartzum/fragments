#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

struct node {
    int k;
    int s;
    void *data;
    struct node *next;
};

struct node *list() {
    struct node *result = malloc(sizeof(struct node));
    result->k = 1;
    result->data = NULL;
    result->s = 0;
    result->next = NULL;
    return result;
}

struct node *list_add(struct node *n, int k, void *data, int s) {
    struct node *result = malloc(sizeof(struct node));
    result->k = k;
    result->data = malloc(s);
    result->s = s;
    result->next = NULL;
    n->next = result;
    memcpy(result->data, data, s);
    return result;
}

void list_for(struct node *n, void (*f)(struct node *i)) {
    struct node *s = n;
    while (s) {
        (*f)(s);
        s = s->next;
    }
}

void list_print(struct node *n) {
    printf("%i, %s\n", n->k, n->data);
}

void list_free(struct node *n) {
    struct node *s = n;
    while (s) {
        struct node *next = s->next;
        free(s->data);
        free(s);
        s = next;
    }
}

void list_for_test() {
    struct node *l = list();
    list_add(l, 2, "123", 3);
    list_for(l, list_print);
    list_free(l);
}

int main() {
    list_for_test();
    return 0;
}