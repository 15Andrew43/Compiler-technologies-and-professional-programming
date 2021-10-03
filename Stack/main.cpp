#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const size_t name_size = 50;
const int guard_value = -2281337;

typedef int elem_t;


struct Stack {
    int left_guard = guard_value;

    size_t size = 0;
    size_t capacity = 0;
    elem_t* data = {};
    const elem_t empty_elem = 1543000000;

    char name[name_size];
    const int delta = 5;
    int error = 0;
    int sum_hash = 0;

    int right_guard = guard_value;
};


Stack StackConstructor(const char* name);
int IncreaseStack(Stack* stack, const int new_capacity, const size_t elem_size);
int StackPush(Stack* stack, elem_t value);
int DecreaseStack(Stack* stack, const int new_capacity, const size_t elem_size);
int StackPop(Stack *stack, elem_t* var);
int StackDestructor(Stack* stack);

bool StkOk(Stack* stack);



int main() {
    Stack stk1 = StackConstructor("stk1");
    for (int i = 0; i < 20; i++) {
        StackPush(&stk1, 10+i);
    }

    int x = 0;
    for (int i = 0; i < 17; i++) {
        StackPop(&stk1, &x);
    }


    int err = StackPop(&stk1, &x);

    StackDestructor(&stk1);
    getchar();
}




Stack StackConstructor(const char* name) {
    const size_t first_capacity = 10;
    Stack stack = {};

    strcpy(stack.name, name);
    stack.error = 0;

//    elem_t emptyelem = stack.empty_elem;
    stack.data = (elem_t*)calloc(first_capacity, sizeof(elem_t));
    memset(stack.data, stack.empty_elem, first_capacity);
    stack.size = 0;
    stack.capacity = first_capacity;

    return stack;
}


int IncreaseStack(Stack* stack, const int new_capacity, const size_t elem_size) {
    stack->data = (elem_t*)realloc(stack->data, new_capacity * elem_size);
    if (stack->data == NULL) {
        return 2;
    }

    elem_t stkemptyelem = stack->empty_elem;
    memset(stack->data, stack->empty_elem, stack->capacity);

    stack->capacity = new_capacity;

    return 0;
}


int StackPush(Stack* stack, elem_t value) {
    assert(stack != NULL);

    if (stack->size == stack->capacity) {
        if (IncreaseStack(stack, stack->capacity * 2, sizeof(elem_t)) != 0) {
            return 2;
        }
    }
    stack->data[stack->size++] = value;
    return 0;
}

int DecreaseStack(Stack* stack, const int new_capacity, const size_t elem_size) {
    assert(stack != NULL);


    stack->data = (elem_t*)realloc(stack->data, new_capacity * elem_size);
    if (stack->data == NULL) {
        return 2;
    }
    stack->capacity = new_capacity;

    return 0;
}

int StackPop(Stack *stack, elem_t* var) {
    assert(stack != NULL);

    int error = 0;
    if (stack->size > 0) {
        *var = stack->data[--stack->size];
        stack->data[stack->size] = stack->empty_elem;

        if (stack->size < (stack->capacity / 2) - stack->delta) {
            assert(stack->data[stack->size] == stack->empty_elem);
            if (DecreaseStack(stack, stack->size + 1, sizeof(elem_t)) != 0) {
                error = 3;
            }
        }
    }
    else {
        error = 2;
    }

    return error;
}

int StackDestructor(Stack* stack) {
    assert(stack != NULL);

    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;

    return 0;
}

bool StkOk(Stack* stack) {
    if (stack->size > stack->capacity) {
        stack->error = 1;
        return false;
    }
    if (stack->size < 0) {
        stack->error = 2;
        return false;
    }
    if (stack->left_guard != guard_value) {
        stack->error = 3;
        return false;
    }
    if (stack->right_guard != guard_value) {
        stack->error = 4;
        return false;
    }
//    if (stack->hash != CalcHash(stack)) {
//        stack->err = 5;
//        return false;
//    }
    stack->error = 0;
    return true;
}