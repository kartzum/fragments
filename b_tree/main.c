#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

// b_tree. Start.

struct b_node {
    int k;
    int s;
    void *data;
    struct b_node *left;
    struct b_node *right;
};

struct b_tree {
    struct b_node *root;
};

struct b_tree *b_tree() {
    return calloc(1, sizeof(struct b_tree));
}

struct b_node *b_node(int k, int s, void *data) {
    struct b_node *n = calloc(1, sizeof(struct b_node));
    n->k = k;
    n->s = s;
    n->data = malloc(s);
    memcpy(n->data, data, s);
    n->left = NULL;
    n->right = NULL;
    return n;
}

void b_tree_add_n(struct b_node *r, int k, int s, void *data) {
    if (k < r->k) {
        if (r->left != NULL) {
            b_tree_add_n(r->left, k, s, data);
        } else {
            r->left = b_node(k, s, data);
        }
    } else {
        if (r->right != NULL) {
            b_tree_add_n(r->right, k, s, data);
        } else {
            r->right = b_node(k, s, data);
        }
    }
}

void b_tree_add(struct b_tree *t, int k, int s, void *data) {
    if (t->root == NULL) {
        t->root = b_node(k, s, data);
    } else {
        b_tree_add_n(t->root, k, s, data);
    }
}

void b_tree_for_n(struct b_node *r, void (*f)(struct b_node *i)) {
    if (r != NULL) {
        (*f)(r);
        if (r->left != NULL) {
            (*f)(r->left);
        }
        if (r->right != NULL) {
            (*f)(r->right);
        }
        if (r->left != NULL) {
            b_tree_for_n(r->left, f);
        }
        if (r->right != NULL) {
            b_tree_for_n(r->right, f);
        }
    }
}

void b_tree_for(struct b_tree *t, void (*f)(struct b_node *i)) {
    b_tree_for_n(t->root, f);
}

void b_tree_printf_i(int k, int s, void *data) {
    int v = *((int *) data);
    printf("%d, %d\n", k, v);
}

void b_tree_printf_n(struct b_node *n) {
    b_tree_printf_i(n->k, n->s, n->data);
}

void b_tree_free_n(struct b_node *n) {
    if (n != NULL) {
        if (n->left != NULL) {
            b_tree_free_n(n->left);
            free(n->left->data);
            free(n->left);
        }
        if (n->right != NULL) {
            b_tree_free_n(n->right);
            free(n->right->data);
            free(n->right);
        }
    }
}

void b_tree_free(struct b_tree *t) {
    b_tree_free_n(t->root);
    free(t->root->data);
    free(t->root);
}

// b_tree. Start.

void b_tree_for_test() {
    struct b_tree *t = b_tree();
    int l1 = 7;
    b_tree_add(t, 7, 1, &l1);
    int l2 = 6;
    b_tree_add(t, 6, 1, &l2);
    int l3 = 5;
    b_tree_add(t, 5, 1, &l3);
    int l4 = 8;
    b_tree_add(t, 8, 1, &l4);
    int l5 = 9;
    b_tree_add(t, 9, 1, &l5);
    b_tree_for(t, b_tree_printf_n);
    b_tree_free(t);
    free(t);
}

int main() {
    b_tree_for_test();
    return 0;
}