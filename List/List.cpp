#include "List.h"

int GetNextFreeInd(List *list_ptr) {
    return list_ptr->nodes[list_ptr->free].next;
}

void GetFree(List *list_ptr) {
    for (int i = list_ptr->free; i < list_ptr->capacity - 1; ++i) {
        list_ptr->nodes[i] = {-1, i + 1, -1};
    }
    list_ptr->nodes[list_ptr->capacity - 1] = {-1, 0, -1};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



List ListConstructor(size_t size) {
    List list;
    list.nodes = (Node*) calloc(start_capacity, sizeof(Node));
    list.head = head_ind;
    list.tail = tail_ind;
    list.free = first_free_ind;
    list.nodes[list.head] = {-1, -1, -1};
    list.nodes[list.tail] = {-1, -1, -1};;
    list.capacity = size;

    GetFree(&list);
    return list;
}



void ListDestructor(List *list_ptr) {
    free(list_ptr->nodes);
}


Error ListPushBack(List *list_ptr, elem_t elem) {
    int free = list_ptr->free;
    list_ptr->free = GetNextFreeInd(list_ptr);
    list_ptr->nodes[free] = {
            elem,
            list_ptr->tail,
            (list_ptr->size ? list_ptr->nodes[list_ptr->tail].prev : list_ptr->head)
    };
    list_ptr->nodes[(list_ptr->size ? list_ptr->nodes[list_ptr->tail].prev : list_ptr->head)].next = free;
    list_ptr->nodes[list_ptr->tail].prev = free;
    return Ok;
}

Error ListPushFront(List *list_ptr, elem_t elem) {
    int free = list_ptr->free;
    list_ptr->free = GetNextFreeInd(list_ptr);
    list_ptr->nodes[free] = {
            elem,
            (list_ptr->size ? list_ptr->nodes[list_ptr->head].next : list_ptr->tail),
            list_ptr->head
    };

    list_ptr->nodes[(list_ptr->size ? list_ptr->nodes[list_ptr->head].next : list_ptr->tail)].prev = free;
    list_ptr->nodes[list_ptr->head].next = free;
    return Ok;
}



Error ListPopBack(List *list_ptr) {
    int next_free = list_ptr->free;
    list_ptr->free = list_ptr->nodes[list_ptr->tail].prev;

    list_ptr->nodes[list_ptr->tail].prev = list_ptr->nodes[list_ptr->nodes[list_ptr->tail].prev].prev;
    list_ptr->nodes[list_ptr->nodes[list_ptr->nodes[list_ptr->tail].prev].prev].next = list_ptr->tail;

    list_ptr->nodes[list_ptr->free] = {-1, next_free, -1};
    return Ok;
}

Error ListPopFront(List *list_ptr) {
    int next_free = list_ptr->free;
    list_ptr->free = list_ptr->nodes[list_ptr->head].next;

    list_ptr->nodes[list_ptr->head].next = list_ptr->nodes[list_ptr->nodes[list_ptr->head].next].next;
    list_ptr->nodes[list_ptr->nodes[list_ptr->nodes[list_ptr->head].next].next].prev = list_ptr->tail;

    list_ptr->nodes[list_ptr->free] = {-1, next_free, -1};
    return Ok;
}

Error ListPush(List *list_ptr, int ind, elem_t elem) {
    int free = list_ptr->free;
    list_ptr->free = GetNextFreeInd(list_ptr);
    list_ptr->nodes[free] = {
            elem,
            ind,
            list_ptr->nodes[ind].prev
    };

    list_ptr->nodes[list_ptr->nodes[ind].prev].next = free;
    list_ptr->nodes[ind].prev = free;
    return Ok;
}

Error ListPop(List *list_ptr, int ind) {
    int next_free = list_ptr->free;
    list_ptr->free = ind;

    list_ptr->nodes[list_ptr->nodes[ind].prev].next = list_ptr->nodes[ind].next;
    list_ptr->nodes[list_ptr->nodes[ind].next].prev = list_ptr->nodes[ind].prev;

    list_ptr->nodes[ind] = {-1, next_free, -1};
    return Ok;
}

Node ListElem(List *list_ptr, int ind) {
    return list_ptr->nodes[ind];
}

