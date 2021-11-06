//
// Created by Андрей Боровец on 06/11/2021.
//

#include "stack.h"



//typedef int elem_t;

//const size_t name_size = 50;
//const int guard_value = -2281337;
//
//const elem_t empty_elem = 1543000000;
//const int delta = 5;







int doCaseStk_OK(Stack* stack) {
#ifdef DEBUG
    if (StkOk(stack)) {
        PrintStk_OK(*stack);
    }
    else {
        PrintStk_NOK(*stack);
        return 1;
    }
#endif
    return 0;
}


//int main() {
//    Stack stack1 = StackConstructor("stack1");
//    for (int i = 0; i < 20; ++i) {
//        StackPush(&stack1, 1000 + i);
//    }
//
//    int x = 0;
//    for (int i = 0; i < 17; ++i) {
//        StackPop(&stack1, &x);
//    }
//
//    StackDestructor(&stack1);
//}





char* elem_tToStr(elem_t elem) {

    const int elem_tMaxStrSize = 20;

    char* str = (char*)calloc(elem_tMaxStrSize, sizeof(char));
//    itoa(elem, str, 10);
    snprintf(str, elem_tMaxStrSize, "%d", elem);
    return str;
}


#ifdef DEBUG
void StackDump(Stack *stack, const char* file, const int line, const char* function, const char* message) {
    char status[10] = "ok";
    if (stack->error != 0) {
        strcpy(status, "ERROR");
    }

    printf("\n%s\n", message);
    printf("\nStack <int> [%p] %s called from %s() at %s(%d).\n", stack,  stack->name, function, file, line);
    printf("STATUS: %s\n", status);
    printf("\tleft_guard = %d\n", stack->left_guard);
    printf("\tsize = %d\n", stack->size);
    printf("\tdelta = %d\n", delta);
    printf("\tcapacity = %d\n", stack->capacity);

    printf("\tdata [%p]:\n", &stack->data);
    for (int i = 0; i < stack->capacity; ++i) {
        char* elemStr = elem_tToStr(stack->data[i]);
        if (stack->data[i] == empty_elem) {
            printf("\t\t[%d] = %s (poison),\n", i, elemStr);
        }
        else {
            printf("\t\t[%d] = %s,\n", i, elemStr);
        }
        free(elemStr);
    }

    printf("\tsum_hash = %u\n", stack->sum_hash);
    printf("\tright_guard = %d\n", stack->right_guard);
    printf("error = %d\n\n\n", stack->error);
}
#endif


Stack StackConstructor(const char* name) {
    const size_t first_capacity = 10;
    Stack stack = {};

#ifdef DEBUG
    strcpy(stack.name, name);
    stack.error = 0;
#endif

    stack.data = (elem_t*)calloc(first_capacity, sizeof(elem_t));
    memset(stack.data, empty_elem, first_capacity);
    stack.size = 0;
    stack.capacity = first_capacity;

#ifdef DEBUG
    RecalcHash(&stack);
#endif

    doCaseStk_OK(&stack);

    return stack;
}


int StackDestructor(Stack* stack) {
    assert(stack != NULL);

#ifdef DEBUG
    if (!StkOk(stack)) {
        PrintStk_NOK(*stack);
        return 1;
    }
#endif

    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;

#ifdef DEBUG
    strcpy(stack->name, "");
    stack->error = 0;
    stack->sum_hash = 0;
#endif

    return 0;
}


int StackPush(Stack* stack, elem_t value) {
    assert(stack != NULL);

#ifdef DEBUG
    if (!StkOk(stack)) {
        PrintStk_NOK(*stack);
        return 1;
    }
#endif

    if (stack->size == stack->capacity) {
        if (IncreaseStack(stack, stack->capacity * 2, sizeof(elem_t)) != 0) {
            return 2;
        }
    }
    stack->data[stack->size++] = value;

#ifdef DEBUG
    RecalcHash(stack);
#endif

    doCaseStk_OK(stack);

    return 0;
}


int StackPop(Stack *stack, elem_t* var) {
    assert(stack != NULL);

    doCaseStk_OK(stack);

    int error = 0;
    if (stack->size > 0) {
        *var = stack->data[--stack->size];
        stack->data[stack->size] = empty_elem;

        if (stack->size < (stack->capacity / 2) - delta) {
            assert(stack->data[stack->size] == empty_elem);
            if (DecreaseStack(stack, stack->size + 1, sizeof(elem_t)) != 0) {
                error = 3;
            }
        }
    }
    else {
        error = 2;
    }

#ifdef DEBUG
    RecalcHash(stack);
#endif

    doCaseStk_OK(stack);

    return error;
}


int IncreaseStack(Stack* stack, const int new_capacity, const size_t elem_size) {
    assert(stack!=NULL);

#ifdef DEBUG
    StackDump(stack, __FILE__, __LINE__, __FUNCTION__, "Before increasing stack");
#endif

    stack->data = (elem_t*)realloc(stack->data, new_capacity * elem_size);
    if (stack->data == NULL) {
        return 2;
    }
    memset(stack->data, empty_elem, stack->capacity);
    stack->capacity = new_capacity;

#ifdef DEBUG
    StackDump(stack, __FILE__, __LINE__, __FUNCTION__, "After increasing stack");

    RecalcHash(stack);
#endif

    doCaseStk_OK(stack);

    return 0;
}


int DecreaseStack(Stack* stack, const int new_capacity, const size_t elem_size) {
    assert(stack != NULL);

#ifdef DEBUG
    StackDump(stack, __FILE__, __LINE__, __FUNCTION__, "Before decreasing stack");
#endif

    stack->data = (elem_t*)realloc(stack->data, new_capacity * elem_size);
    if (stack->data == NULL) {
        return 2;
    }
    stack->capacity = new_capacity;


#ifdef DEBUG
    StackDump(stack, __FILE__, __LINE__, __FUNCTION__, "After decreasing stack");

    RecalcHash(stack);
#endif

    doCaseStk_OK(stack);

    return 0;
}





#ifdef DEBUG
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
    if (stack->sum_hash != CalcHash(stack)) {
        stack->error = 5;
        return false;
    }
    stack->error = 0;
    return true;
}
#endif


#ifdef DEBUG
size_t CalcHash(Stack* stack) {
    assert(stack != NULL);

    size_t hash = 0;
    for (int i = 0; i < stack->capacity; ++i) {
        for (int j = 0; j < sizeof(elem_t); ++j) {
            char curByte = *((char*)& stack->data[i] + j);
            hash += curByte*2;
        }
    }
    for (int j = 0; j < sizeof(int); ++j) {
        char curByte = *((char*)& delta + j);
        hash += curByte * 2;
    }
    for (int j = 0; j < sizeof(int); ++j) {
        char curByte = *((char*)& stack->capacity + j);
        hash += curByte * 2;
    }
    for (int j = 0; j < sizeof(int); ++j) {
        char curByte = *((char*)& stack->size + j);
        hash += curByte * 2;
    }
    for (int j = 0; j < sizeof(elem_t); ++j) {
        char curByte = *((char*)& empty_elem + j);
        hash += curByte * 2;
    }

#ifdef DEBUG
    for (int i = 0; i < 30; ++i) {
        char curByte = stack->name[i];
        hash += curByte * 2;
    }
    for (int j = 0; j < sizeof(elem_t); ++j) {
        char curByte = *((char*)& stack->error + j);
        hash += curByte * 2;
    }
#endif
    return hash;
}
#endif


#ifdef DEBUG
size_t RecalcHash(Stack *stack) {
    assert(stack != NULL);

    stack->sum_hash = CalcHash(stack);

#ifdef DEBUG
    if (!StkOk(stack)) {
        PrintStk_NOK(*stack);
        return 2;
    }
#endif

    return 0;
}
#endif