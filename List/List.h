#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iostream>
#include <utility>
#include <cstdlib>
#include <iomanip>

#include <sys/stat.h>



const size_t start_capacity = 100;
const int head_ind = 0;
const int tail_ind = 1;
const int first_free_ind = 2;
const size_t MAX_LENGTH = 256;
const size_t graphiz_size = 10000;


const int alignment = 3;

typedef int elem_t;

enum Error {
    Ok=0,
};


struct Node {
    elem_t data;
    int next;
    int prev;
};


struct List {
    Node *nodes;

    int head;
    int tail;
    int free;

    size_t capacity = start_capacity;
    size_t size = 0;
};



List ListConstructor(size_t size = start_capacity);

void ListDestructor(List *list);

Error ListPushBack(List *list_ptr, elem_t elem);

Error ListPushFront(List *list_ptr, elem_t elem);

Error ListPopBack(List *list_ptr);

Error ListPopFront(List *list_ptr);

Error ListPush(List *list_ptr, int ind, elem_t elem);

Error ListPop(List *list_ptr, int ind);

Node ListElem(List *list_ptr, int ind);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GetNextFreeInd(List *list_ptr);

void ListPrint(List *list_ptr);

void ListDraw(List *list_ptr, const char *file_name="beautiful_picture.txt");

void GetFree(List *list_ptr);

int getCntLines(FILE *file);

int getFileSize(FILE *file);


#endif //LIST_LIST_H
