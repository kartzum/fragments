#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

// lm_vm. Start.

struct lm_vm_op_code_data {
    char iconst_m1;  // load the int value −1 onto the stack
    char iadd;       // add two ints
};

struct lm_vm_stack_command_data {
    char i;
};

struct lm_vm_y_node {
    int k;
    int s;
    void *data;
};

struct lm_vm_y_array {
    struct lm_vm_y_node **data;
    int size;
};

struct lm_vm_vm {
    int code_size;
    char *code;
    int stack_size;
    long *stack;
    int ip;
    int sp;
    struct lm_vm_y_array *storage;
    int storage_type_int;
    int storage_i_m1_index;
};

struct lm_vm_op_code_data *lm_vm_op_code_data() {
    struct lm_vm_op_code_data *result = calloc(1, sizeof(struct lm_vm_op_code_data));
    result->iconst_m1 = 2;
    result->iadd = 96;
    return result;
}

void lm_vm_op_code_data_free(struct lm_vm_op_code_data **op_code_data) {
    struct lm_vm_op_code_data *op_code_data_i = *op_code_data;
    free(op_code_data_i);
}

struct lm_vm_stack_command_data *lm_vm_stack_command_data() {
    struct lm_vm_stack_command_data *result = calloc(1, sizeof(struct lm_vm_stack_command_data));
    result->i = 1;
    return result;
}

void lm_vm_stack_command_data_free(struct lm_vm_stack_command_data **stack_command_data) {
    struct lm_vm_stack_command_data *stack_command_data_i = *stack_command_data;
    free(stack_command_data_i);
}

struct lm_vm_y_array *lm_vm_y_array() {
    struct lm_vm_y_array *result = calloc(1, sizeof(struct lm_vm_y_array));
    result->size = 2;
    return result;
}

struct lm_vm_y_node **lm_vm_y_array_alloc(struct lm_vm_y_array *a) {
    struct lm_vm_y_node **d = NULL;
    if (a->data == NULL) {
        d = calloc(1, sizeof(struct lm_vm_y_node *) * a->size);
        a->data = d;
    } else {
        d = a->data;
    }
    return d;
}

struct lm_vm_y_node **lm_vm_y_array_realloc(struct lm_vm_y_array *a) {
    struct lm_vm_y_node **d = NULL;
    if (a->data == NULL) {
        d = calloc(1, sizeof(struct lm_vm_y_node *) * a->size);
        a->data = d;
    } else {
        d = realloc(a->data, sizeof(struct lm_vm_y_node *) * a->size);
        a->data = d;
    }
    return d;
}

struct lm_vm_y_node **lm_vm_y_array_data(struct lm_vm_y_array *a, int i) {
    struct lm_vm_y_node **d = NULL;
    if (i >= 0) {
        if (i < a->size) {
            d = lm_vm_y_array_alloc(a);
        } else if (i < a->size * 2) {
            a->size = a->size * 2;
            d = lm_vm_y_array_realloc(a);
        } else {
            a->size = a->size * ((i / a->size) + 1);
            d = lm_vm_y_array_realloc(a);
        }
    }
    return d;
}

void lm_vm_y_array_set(struct lm_vm_y_array *a, int i, int k, int s, void *data) {
    struct lm_vm_y_node **d = lm_vm_y_array_data(a, i);
    if (d != NULL) {
        struct lm_vm_y_node *node = calloc(1, sizeof(struct lm_vm_y_node));
        node->data = malloc(s);
        node->s = s;
        node->k = k;
        memcpy(node->data, data, s);
        d[i] = node;
    }
}

struct lm_vm_y_node *lm_vm_y_array_get_i(struct lm_vm_y_array *a, int i) {
    struct lm_vm_y_node *result = NULL;
    if (i >= 0 && i < a->size) {
        struct lm_vm_y_node **d = a->data;
        result = d[i];
    }
    return result;
}

void lm_vm_y_array_free(struct lm_vm_y_array **a) {
    struct lm_vm_y_array *a_i = *a;
    struct lm_vm_y_node **d = a_i->data;
    for (int i = 0; i < a_i->size; i++) {
        if (d[i] != NULL) {
            free(d[i]->data);
            free(d[i]);
            d[i] = NULL;
        }
    }
    free(a_i);
}

void lm_vm_vm_storage_add_int(struct lm_vm_vm *vm, int i, int v) {
    lm_vm_y_array_set(vm->storage, i, vm->storage_type_int, sizeof(int), &v);
}

int lm_vm_vm_storage_get_int(struct lm_vm_vm *vm, int i) {
    struct lm_vm_y_node *node = lm_vm_y_array_get_i(vm->storage, i);
    int v = *((int *) node->data);
    return v;
}

struct lm_vm_vm *lm_vm_vm(int code_size, char *code) {
    struct lm_vm_vm *vm = calloc(1, sizeof(struct lm_vm_vm));
    vm->code = malloc(code_size);
    vm->code_size = code_size;
    memcpy(vm->code, code, code_size);
    vm->stack_size = 100;
    vm->stack = calloc(vm->stack_size, sizeof(long));
    vm->ip = 0;
    vm->sp = -1;
    struct lm_vm_y_array *storage = lm_vm_y_array();
    vm->storage = storage;
    vm->storage_type_int = 1;
    vm->storage_i_m1_index = 0;
    lm_vm_vm_storage_add_int(vm, vm->storage_i_m1_index, -1);
    return vm;
}

void lm_vm_vm_free(struct lm_vm_vm **vm) {
    struct lm_vm_vm *vm_i = *vm;
    lm_vm_y_array_free(&vm_i->storage);
    free(vm_i->code);
    free(vm_i->stack);
    free(vm_i);
}

void lm_vm_trace_code(struct lm_vm_vm *vm) {
    printf("%d:%d\n", vm->ip, vm->code[vm->ip]);
}

long lm_vm_pack(int a, int b) {
    return (long) a << 32 | b & 0xFFFFFFFFL;
}

void lm_vm_unpack(long c, int *a, int *b) {
    *a = (int) (c >> 32);
    *b = (int) (c);
}

void lm_vm_vm_exec(
        struct lm_vm_vm *vm,
        struct lm_vm_op_code_data *op_code_data,
        struct lm_vm_stack_command_data *stack_command_data,
        bool trace) {
    char o = vm->code[vm->ip];
    while (vm->ip < vm->code_size) {
        if (trace) {
            lm_vm_trace_code(vm);
        }
        vm->ip++;
        if (op_code_data->iconst_m1 == o) {
            vm->sp++;
            long d = lm_vm_pack(stack_command_data->i, lm_vm_vm_storage_get_int(vm, vm->storage_i_m1_index));
            vm->stack[vm->sp] = d;
        } else if (op_code_data->iadd == o) {
            int c0 = 0;
            int v0 = 0;
            long d0 = vm->stack[vm->sp];
            lm_vm_unpack(d0, &c0, &v0);
            vm->sp--;
            int c1 = 0;
            int v1 = 0;
            long d1 = vm->stack[vm->sp];
            lm_vm_unpack(d1, &c1, &v1);
            vm->sp--;
            vm->sp++;
            long d = lm_vm_pack(stack_command_data->i, v0 + v1);
            vm->stack[vm->sp] = d;
        }
        o = vm->code[vm->ip];
    }
}

// lm_vm. Finish.

void lm_vm_init_test(bool trace) {
    struct lm_vm_op_code_data *op_code_data = lm_vm_op_code_data();
    struct lm_vm_stack_command_data *stack_command_data = lm_vm_stack_command_data();
    int code_size = 5;
    char *code = calloc(code_size, sizeof(char));
    code[0] = op_code_data->iconst_m1;
    code[1] = op_code_data->iconst_m1;
    code[2] = op_code_data->iadd;
    struct lm_vm_vm *vm = lm_vm_vm(code_size, code);
    lm_vm_vm_exec(vm, op_code_data, stack_command_data, trace);
    free(code);
    lm_vm_vm_free(&vm);
    lm_vm_op_code_data_free(&op_code_data);
    lm_vm_stack_command_data_free(&stack_command_data);
}

void lm_vm_test(bool trace) {
    lm_vm_init_test(trace);
}

int main() {
    bool trace = true;
    lm_vm_test(trace);
    return 0;
}