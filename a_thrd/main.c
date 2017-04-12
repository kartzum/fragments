#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

// Creation. Start.

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

// Creation. Finish.

// Simple-Mutex. Start.

int simple_mutex_counter = 0;

pthread_mutex_t simple_mutex_lock;

bool simple_mutex_flag = true;

void *simple_mutex_function(void *data) {
    int *n = (int *) (data);
    int k = *n;

    if (simple_mutex_flag) {
        pthread_mutex_lock(&simple_mutex_lock);
    }

    int j = 0;
    while (j < 20000) {
        simple_mutex_counter++;

        int i = 0;
        while (i < 10000) {
            i++;
        }

        j++;
    }
    printf("%d: %d\n", k, simple_mutex_counter);

    if (simple_mutex_flag) {
        pthread_mutex_unlock(&simple_mutex_lock);
    }

    return NULL;
}

void simple_mutex_test() {
    pthread_mutex_init(&simple_mutex_lock, NULL);

    pthread_t threads[2];
    int i = 0;
    while (i < 2) {
        pthread_create(&(threads[i]), NULL, simple_mutex_function, &threads[i]);
        i++;
    }
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&simple_mutex_lock);
}

// Simple-Mutex. Finish.

int main() {
    // creation_test();
    simple_mutex_test();
    return 0;
}