#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

struct node {
    void *data;
    int size;
    int type;
    struct node *next;
};

struct node *list() {
    struct node *result = malloc(sizeof(struct node));
    result->type = 1;
    result->data = 0;
    result->size = 0;
    result->next = 0;
    return result;
}

struct node *list_add(struct node *n, int type, void *data, int size) {
    struct node *result = malloc(sizeof(struct node));
    result->type = type;
    result->data = malloc(size);
    result->size = size;
    result->next = 0;
    n->next = result;
    memcpy(result->data, data, size);
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
    printf("%i, %s\n", n->type, n->data);
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
}