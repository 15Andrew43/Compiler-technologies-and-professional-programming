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

int getCntLines(FILE *file) {
    fseek(file , 0, SEEK_SET);

    char tmp_line[MAX_LENGTH] = "";

    int cnt_lines = 0;
    while(!feof (file)) {
        if (fgets(tmp_line, MAX_LENGTH, file)) {
            ++cnt_lines;
        }
    }

    return cnt_lines;
}

int getFileSize(FILE *file) {
    struct stat st;

    if ((fstat(fileno(file), &st) != 0) || (!S_ISREG(st.st_mode))) {
        return -1;
    }

    return st.st_size;
}

void ListDraw(List *list_ptr, const char *file_name) {
    char buffer[MAX_LENGTH] = {};
    char str_number[20];
    char tmp[MAX_LENGTH] = {};

    FILE *file = fopen(file_name, "w");

    strcpy(
            tmp,
            "digraph structs {\n"
            "    newrank=true;\n"
            "    rankdir = LR;\n"
            "\n"
            "    {\n"
            "        node[shape=plaintext];\n"
            "        edge[color=white]\n"
            );
    fwrite(tmp, sizeof(char), strlen(tmp), file);



    int ind = 0;
    for (int i = 0; i < list_ptr->capacity; ++i) {

        sprintf(str_number, "%d", i);
        sprintf(buffer + ind, "%d", i);
        ind += strlen(str_number);
        if (i == list_ptr->capacity - 1) {
            sprintf(buffer + ind, ";");
            ++ind;
        } else {
            sprintf(buffer + ind, "->");
            ind += 2;
        }
    }
    fwrite(buffer, sizeof(char), strlen(buffer), file);
    buffer[0] = '\0';
    strcpy(tmp, "\n    }\n\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);



    for (int i = 0; i < list_ptr->capacity; ++i) {

        strcpy(tmp, "subgraph cluster");
        sprintf(buffer, "%s", tmp);
        sprintf(str_number, "%d", i);
        strcat(buffer, str_number);
        strcat(buffer, " {\n");
        fwrite(buffer, sizeof(char), strlen(buffer), file);

        buffer[0] = '\0';

        if (i == 0) {
            strcpy(
                    tmp,
                    "node [color=white];\n"
                    "       style=filled;\n"
                    "       color=lightblue;\n"
            );
        } else if (i == 1) {
            strcpy(
                    tmp,
                    "node [color=white];\n"
                    "       style=filled;\n"
                    "       color=lightgreen;\n"
            );
        } else {
            strcpy(
                    tmp,
                    "node [color=white];\n"
                    "       style=filled;\n"
                    "       color=lightgrey;\n"
            );
        }
        strcat(buffer, tmp);
        strcat(buffer, "a");
        strcat(buffer, str_number);
//        strcat(buffer, " [shape=record, style=filled, label = \"address\"];\n");
        strcat(buffer, " [shape=record, style=filled, label = ");
        strcat(buffer, str_number);
        strcat(buffer, "]\n");
        strcat(buffer, "b");
        strcat(buffer, str_number);
//        strcat(buffer, " [shape=record, label=\" <data>data | <next>next | <prev>prev\" ];\n");
        strcat(buffer, " [shape=record, label=\" <data>data:");
        sprintf(str_number, "%d", list_ptr->nodes[i].data);
        strcat(buffer, str_number);
//        strcat(buffer, " | <next>next | <prev>prev\" ];\n");
        strcat(buffer, " | <next>next:");
        sprintf(str_number, "%d", list_ptr->nodes[i].next);
        strcat(buffer, str_number);
        strcat(buffer, " | <prev>prev:");
        sprintf(str_number, "%d", list_ptr->nodes[i].prev);
        strcat(buffer, str_number);

        strcat(buffer, "\" ];\n}\n\n\n");
        fwrite(buffer, sizeof(char), strlen(buffer), file);

        buffer[0] = '\0';
    }

    strcpy(tmp, "  { rank = same; ");
    for (int i = 0; i < list_ptr->capacity; ++i) {
        sprintf(buffer, "%s%d; a%d; b%d;}\n", tmp, i, i, i);
        fwrite(buffer, sizeof(char), strlen(buffer), file);
    }


    strcpy(tmp, "\n\n\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);

    strcpy(tmp, "edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);


    for (int i = 0; i < list_ptr->capacity - 1; ++i) {
        if (list_ptr->nodes[i].next == -1) {
            continue;
        }
        sprintf(buffer, "b%d:<next> -> a%d\n", i, list_ptr->nodes[i].next);
        fwrite(buffer, sizeof(char), strlen(buffer), file);
    }

    strcpy(tmp, "\n\n\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);

    strcpy(tmp, "edge[color=\"red\",fontcolor=\"blue\",fontsize=12];\n\n\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);


    for (int i = list_ptr->capacity-1; i > 0; --i) {
        if (list_ptr->nodes[i].prev == -1) {
            continue;
        }
        sprintf(buffer, "b%d:<prev> -> a%d\n", i, list_ptr->nodes[i].prev);
        fwrite(buffer, sizeof(char), strlen(buffer), file);
    }

    strcpy(tmp, "\n}\n");
    fwrite(tmp, sizeof(char), strlen(tmp), file);


    fclose(file);
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



