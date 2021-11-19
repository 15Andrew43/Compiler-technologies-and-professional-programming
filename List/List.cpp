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


void ListPrint(List *list_ptr) {
    printf("size = %d\n", list_ptr->size);
    printf("capacity = %d\n", list_ptr->capacity);
    printf("free = %d\n", list_ptr->free);
    printf("head = %d\n", list_ptr->head);
    printf("tail = %d\n", list_ptr->tail);

    printf("inds | ");
    for (int i = 0; i < list_ptr->capacity; ++i) {
        std::cout << std::setw(alignment) << i;
//        printf("%d ", list_ptr->nodes[i].data);
    }
    printf("\n");
    printf("data | ");
    for (int i = 0; i < list_ptr->capacity; ++i) {
        std::cout << std::setw(alignment) << list_ptr->nodes[i].data;
//        printf("%d ", list_ptr->nodes[i].data);
    }
    printf("\n");
    printf("next | ");
    for (int i = 0; i < list_ptr->capacity; ++i) {
        std::cout << std::setw(alignment) << list_ptr->nodes[i].next;
//        printf("%d ", list_ptr->nodes[i].next);
    }
    printf("\n");
    printf("prev | ");
    for (int i = 0; i < list_ptr->capacity; ++i) {
        std::cout << std::setw(alignment) << list_ptr->nodes[i].prev;
//        printf("%d ", list_ptr->nodes[i].prev);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



List ListConstructor(size_t size) {
    List list;
    list.size = 0;
    list.head = head_ind;
    list.tail = tail_ind;
    list.free = first_free_ind;
    list.capacity = size;
    list.nodes = (Node*) calloc(size, sizeof(Node));
    list.nodes[list.head] = {-1, -1, -1};
    list.nodes[list.tail] = {-1, -1, -1};

//    ListPrint(&list);
//    printf("\n\n");

    GetFree(&list);

//    ListPrint(&list);
//    printf("\n\n");

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

    ++list_ptr->size;
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

    ++list_ptr->size;
    return Ok;
}



Error ListPopBack(List *list_ptr) {
    int next_free = list_ptr->free;
    list_ptr->free = list_ptr->nodes[list_ptr->tail].prev;

    list_ptr->nodes[list_ptr->tail].prev = list_ptr->nodes[list_ptr->nodes[list_ptr->tail].prev].prev;
    list_ptr->nodes[list_ptr->nodes[list_ptr->tail].prev].next = list_ptr->tail;

    list_ptr->nodes[list_ptr->free] = {-1, next_free, -1};

    --list_ptr->size;
    return Ok;
}

Error ListPopFront(List *list_ptr) {
    int next_free = list_ptr->free;
    list_ptr->free = list_ptr->nodes[list_ptr->head].next;

    list_ptr->nodes[list_ptr->head].next = list_ptr->nodes[list_ptr->nodes[list_ptr->head].next].next;
    list_ptr->nodes[list_ptr->nodes[list_ptr->nodes[list_ptr->head].next].next].prev = list_ptr->tail;

    list_ptr->nodes[list_ptr->free] = {-1, next_free, -1};

    --list_ptr->size;
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

    ++list_ptr->size;
    return Ok;
}

Error ListPop(List *list_ptr, int ind) {
    int next_free = list_ptr->free;
    list_ptr->free = ind;

    list_ptr->nodes[list_ptr->nodes[ind].prev].next = list_ptr->nodes[ind].next;
    list_ptr->nodes[list_ptr->nodes[ind].next].prev = list_ptr->nodes[ind].prev;

    list_ptr->nodes[ind] = {-1, next_free, -1};

    --list_ptr->size;
    return Ok;
}

Node ListElem(List *list_ptr, int ind) {
    return list_ptr->nodes[ind];
}

