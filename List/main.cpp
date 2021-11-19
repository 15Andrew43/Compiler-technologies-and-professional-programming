#include <stdio.h>
#include "List.h"



int main() {
    List list = ListConstructor(20);

    ListPrint(&list);
    printf("\n\n");

    for (int i = 0; i < 5; ++i) {
        ListPushBack(&list, i);
    }
    ListPrint(&list);
    printf("\n\n");

    for (int i = 0; i < 2; ++i) {
        ListPopBack(&list);
    }
    ListPrint(&list);
    printf("\n\n");

    ListPush(&list, 3, 33);

    ListPrint(&list);
    printf("\n\n");

    ListPop(&list, 4);

    ListPrint(&list);
    printf("\n\n");


    ListPop(&list, 2);

    ListPrint(&list);
    printf("\n\n");

    return 0;
}


