//
// Created by Андрей Боровец on 06/11/2021.
//

#ifndef CPU_STACK_H
#define CPU_STACK_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//#define DEBUG


#ifdef DEBUG
#define PrintStk_OK(stack) StackDump(&stack, __FILE__, __LINE__, __FUNCTION__, "Just dump");
#define PrintStk_NOK(stack) StackDump(&stack, __FILE__, __LINE__, __FUNCTION__, "Dump with wrong stack");
#endif


typedef int elem_t;

const size_t name_size = 50;
const int guard_value = -2281337;

const elem_t empty_elem = 1543000000;
const int delta = 5;



struct Stack {
#ifdef DEBUG
    int left_guard = guard_value;
#endif

    size_t size = 0;
    elem_t* data = {};
    size_t capacity = 0;


#ifdef DEBUG
    char name[name_size];

    int error = 0;
    int sum_hash = 0;

    int right_guard = guard_value;
#endif
};



Stack StackConstructor(const char* name);
int StackDestructor(Stack* stack);
int StackPush(Stack* stack, elem_t value);
int StackPop(Stack *stack, elem_t* var);
int IncreaseStack(Stack* stack, const int new_capacity, const size_t elem_size);
int DecreaseStack(Stack* stack, const int new_capacity, const size_t elem_size);

bool StkOk(Stack* stack);
size_t CalcHash(Stack* stack);
size_t RecalcHash(Stack *stack);

char* elem_tToStr(elem_t elem);
void StackDump(Stack *stack, const char* file, const int line, const char* function, const char* message);


int doCaseStk_OK(Stack* stack);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //CPU_STACK_H
