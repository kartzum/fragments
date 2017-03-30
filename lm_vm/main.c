#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

// lm_vm. Start.

struct lm_vm_op_code_data {
    char iconst_m1;  // load the int value −1 onto the stack
    char iadd;       // add two ints
};

struct lm_vm_vm {
    int code_size;
    char *code;
    int stack_size;
    long *stack;
    int ip;
    int sp;
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

struct lm_vm_vm *lm_vm_vm(int code_size, char *code) {
    struct lm_vm_vm *vm = calloc(1, sizeof(struct lm_vm_vm));
    vm->code = malloc(code_size);
    vm->code_size = code_size;
    memcpy(vm->code, code, code_size);
    vm->stack_size = 100;
    vm->stack = calloc(vm->stack_size, sizeof(long));
    vm->ip = 0;
    vm->sp = -1;
    return vm;
}

void lm_vm_vm_free(struct lm_vm_vm **vm) {
    struct lm_vm_vm *vm_i = *vm;
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

void lm_vm_vm_exec(struct lm_vm_vm *vm, struct lm_vm_op_code_data *op_code_data, bool trace) {
    char o = vm->code[vm->ip];
    while (vm->ip < vm->code_size) {
        if (trace) {
            lm_vm_trace_code(vm);
        }
        vm->ip++;
        if (op_code_data->iconst_m1 == o) {
            vm->sp++;
            long d = lm_vm_pack(1, -1);
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
            long d = lm_vm_pack(2, v0 + v1);
            vm->stack[vm->sp] = d;
        }
        o = vm->code[vm->ip];
    }
}

// lm_vm. Finish.

void lm_vm_init_test(bool trace) {
    struct lm_vm_op_code_data *op_code_data = lm_vm_op_code_data();
    int code_size = 5;
    char *code = calloc(code_size, sizeof(char));
    code[0] = op_code_data->iconst_m1;
    code[1] = op_code_data->iconst_m1;
    code[2] = op_code_data->iadd;
    struct lm_vm_vm *vm = lm_vm_vm(code_size, code);
    lm_vm_vm_exec(vm, op_code_data, trace);
    free(code);
    lm_vm_vm_free(&vm);
    lm_vm_op_code_data_free(&op_code_data);
}

void lm_vm_test(bool trace) {
    lm_vm_init_test(trace);
}

int main() {
    bool trace = true;
    lm_vm_test(trace);
    return 0;
}