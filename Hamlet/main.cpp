#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>

const int MAX_LENGTH = 256;


void PrintSeparation();
void Print(char** text, int cnt_lines);

int comp (const void* a, const void* b);
int reverse_comp(const void* a, const void* b);

char** ParseFileToArray(const char* string, const int cnt_lines);

int getCntLines(const char *name);
char** Copy(char** text, const int cnt_elem);
void Free(char** str,char** copied_str, const int size);
char* Reverse(char* str, const int size);

void MyQiuckSort(char** base, size_t num, size_t size, int (*compare) (const void *, const void *));






int main() {
    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
    int cnt_lines = getCntLines(file_name);

    char** text = ParseFileToArray(file_name, cnt_lines);
    char** sorted_text = Copy(text, cnt_lines);

    qsort(sorted_text, cnt_lines, sizeof(char*), comp);
    Print(sorted_text, cnt_lines);
    PrintSeparation();

    MyQiuckSort(sorted_text, cnt_lines - 1, sizeof(char*), reverse_comp);
    Print(sorted_text, cnt_lines);
    PrintSeparation();

    Print(text, cnt_lines);


    Free(text, sorted_text, cnt_lines);
    return 0;
}




void PrintSeparation() {
    printf("\n\n\n===========================================================================================\n\n\n");
}

void Print(char** text, int cnt_lines) {
    for (int i = 0; i < cnt_lines; ++i) {
        printf("%s", text[i]);
    }
}



int comp (const void* a, const void* b) {
    return strcmp(*(char**)a,*(char**)b); // wwwwwwwwwwhhhhhhhhhhyyyyyyyyyyy not strcmp( (char*)a, (char*)b )
}

int reverse_comp(const void* a, const void* b) {
    char* first = *(char**)a; // wwwwwwhhhhhhyyyyyy
    char* second = *(char**)b;
    int size_first = strlen(first);
    int size_second = strlen(second);
    char* reverse_first = Reverse(first, size_first);
    char* reverse_second = Reverse(second, size_second);
    int res_cmp = strcmp(reverse_first, reverse_second);
    free(reverse_first);
    free(reverse_second);
    return res_cmp;
}



char** ParseFileToArray(const char* file_name, const int cnt_lines) {
    char cur_line[MAX_LENGTH] = "";

    char** text = (char**) calloc(cnt_lines, sizeof(char*));

    FILE* file = fopen(file_name,"r");

    if(file == NULL) {
        printf("can not open file '%s'", file_name);
        return NULL;
    }
    int ind_line = 0;
    while(!feof (file)) {
        if (fgets(cur_line, MAX_LENGTH, file)) {
            int line_size = strlen(cur_line);
            text[ind_line] = (char*) calloc(line_size + 1, sizeof(char));
            strcpy(text[ind_line], cur_line);
            ++ind_line;
        }
    }
    fclose(file);
    return text;
}



int getCntLines(const char* name) {
    char tmp_line[MAX_LENGTH] = "";

    FILE* file = fopen(name, "r");

    if(file == NULL) {
        printf("can not open file '%s' in getCntLines", name);
        return NULL;
    }
    int cnt_lines = 0;
    while(!feof (file)) {
        if (fgets(tmp_line, MAX_LENGTH, file)) {
            ++cnt_lines;
        }
    }
    fclose(file);
    return cnt_lines;
}

char** Copy(char** text, const int cnt_elem) {
    char** new_text = (char**) calloc(cnt_elem, sizeof(char*));
    for (int i = 0; i < cnt_elem; ++i) {
        new_text[i] = text[i];
    }
    return new_text;
}

void Free(char** str, char** copied_str, const int size) {
    for (int i = 0; i < size; ++i) {
        free(str[i]);
    }
    free(str);
    free(copied_str);
}

char* Reverse(char* str, const int size) {
    char* reverse_str = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; ++i) {
        reverse_str[size - i - 1] = str[i];
    }
    return reverse_str;
}






void MyQiuckSort(char** base, size_t num, size_t size, int (*cmp)(const void *, const void *)) {
    int first = 0;
    int last = num;
    char** array = base;
    if (first < last)
    {
        int left = first, right = last, middle = (left + right) / 2;
        do
        {
            while (cmp(&array[left], &array[middle]) < 0) { // wwwwwwwhhhhhhhyyyyyyyy
                ++left;
            }
            while (cmp(&array[right], &array[middle]) > 0) {
                --right;
            }
            if (left <= right)
            {
                char* tmp = array[left];
                array[left] = array[right];
                array[right] = tmp;
                ++left;
                --right;
            }
        } while (left <= right);

        MyQiuckSort(array, right - first, size, cmp);
        MyQiuckSort(array + left, last - left, size, cmp);
    }
}