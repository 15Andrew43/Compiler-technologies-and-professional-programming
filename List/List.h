#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <utility>

typedef int elem_t;

struct List {
    elem_t* data;

    elem_t* head;
    elem_t* tail;

    elem_t* next;
    elem_t* prev;
};

List ListConstructor(size_t size);

void ListDestructor();


#endif //LIST_LIST_H
