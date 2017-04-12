#include <pthread.h>
#include <stdio.h>

void *creation_inc(void *data) {
    int *x = (int *) data;
    while ((*x) < 100) {
        (*x)++;
    }
    return NULL;
}

void creation_test() {
    pthread_t t;
    int x = 0;
    pthread_create(&t, NULL, creation_inc, &x);
    pthread_join(t, NULL);
    printf("%d", x);
}

int main() {
    creation_test();
    return 0;
}