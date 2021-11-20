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

    for (int i = 20; i < 25; ++i) {
        ListPushFront(&list, i);
    }

    ListPrint(&list);
    printf("\n\n");


    const char path[] = "/Users/andrew_borovets/Desktop/PROGA/DED/Compiler-technologies-and-professional-programming/List/beautiful_picture.txt";
    ListDraw(&list, path);


    return 0;
}

