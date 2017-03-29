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
    int *stack;
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
    vm->stack = calloc(vm->stack_size, sizeof(int));
    return vm;
}

void lm_vm_vm_free(struct lm_vm_vm **vm) {
    struct lm_vm_vm *vm_i = *vm;
    free(vm_i->code);
    free(vm_i->stack);
    free(vm_i);
}

void lm_vm_trace_code(struct lm_vm_vm *vm, int ip) {
    printf("%d:%d\n", ip, vm->code[ip]);
}

void lm_vm_vm_exec(struct lm_vm_vm *vm, struct lm_vm_op_code_data *op_code_data, bool trace) {
    int ip = 0;
    int sp = -1;

    char o = vm->code[ip];
    while (ip < vm->code_size) {
        if (trace) {
            lm_vm_trace_code(vm, ip);
        }
        ip++;
        if (op_code_data->iconst_m1 == o) {
            vm->stack[++sp] = -1;
        } else if(op_code_data->iadd == o) {
            int v0 = vm->stack[sp--];
            int v1 = vm->stack[sp--];
            vm->stack[++sp] = v0 + v1;
        }
        o = vm->code[ip];
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