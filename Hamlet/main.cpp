#include <stdio.h>
#include <cstring>
#include <stdlib.h>

const int MAX_LENGTH = 256;


void PrintSeparation();
void Print(char** text, int cnt_lines);
void PrintBeginning(const char* string);
void PrintEnd(const char* string);

int comp (const void* a, const void* b);
int reverse_comp(const void* a, const void* b);

char** ParseFileToArray(const char* string, const int cnt_lines);

int getCntLines(const char *name);
char** Copy(char** text, const int cnt_elem);
void Free(char** str,char** copied_str, const int size);
char* Reverse(char* str, const int size);

void MyQiuckSort(char** base, size_t num, size_t size, int (*compare) (const void *, const void *));




int main() {
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
    int cnt_lines = getCntLines(file_name);

    char** text = ParseFileToArray(file_name, cnt_lines);
    char** sorted_text = Copy(text, cnt_lines);


    qsort(sorted_text, cnt_lines, sizeof(char*), comp);
    PrintBeginning("Sorted 'Hamlet' by the beginning of the lines:");
    Print(sorted_text, cnt_lines);
    PrintEnd("");
    PrintSeparation();

    MyQiuckSort(sorted_text, cnt_lines - 1, sizeof(char*), reverse_comp);
    PrintBeginning("Sorted 'Hamlet' by the end of the lines:");
    Print(sorted_text, cnt_lines);
    PrintEnd("");
    PrintSeparation();

    PrintBeginning("Original Hamlet");
    Print(text, cnt_lines);
    PrintEnd("");


    Free(text, sorted_text, cnt_lines);
    return 0;
}

void PrintEnd(const char* string) {
    printf("%s\n", string);
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/end.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/end.txt";
    int cnt_lines = getCntLines(file_name);
    char** end = ParseFileToArray(file_name, cnt_lines);
    Print(end, cnt_lines);
}

void PrintBeginning(const char* string) {
    printf("%s\n", string);
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
    int cnt_lines = getCntLines(file_name);
    char** beginning = ParseFileToArray(file_name, cnt_lines);
    Print(beginning, cnt_lines);
}

void PrintSeparation() {
    printf("\n\n\n===========================================================================================\n\n\n");
}

//==========================================================================
//! Prints array[][]: one elem in one string
//!
//! \param [int]    text
//! \param [in]     cnt_lines   count of elements(lines) in text
//==========================================================================
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


//==========================================================================
//! Opens file, reads it line by line
//!             and save every line to dynamic memory
//!
//! \param [in]     file_name       name of file in format "/Users/.../file_name"
//! \param [in]     cnt_lines       count of lines in file
//! \return array[][], where array[i] is i-st line in text
//==========================================================================
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


//==========================================================================
//! Counts number of lines in file
//!
//! \param [in]     name    name of file in format "/Users/.../file_name"
//! \return number of lines in file
//==========================================================================
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

//==========================================================================
//! Copies array[][] to a new_array[][]
//!
//! \param [in]     text        the original array
//! \param [in]     cnt_elem    count of elements in array
//! \return new_array[][]
//!
//! P.S. only array[i][] (i = 1...cnt_elem) will be copied
//==========================================================================
char** Copy(char** text, const int cnt_elem) {
    char** new_text = (char**) calloc(cnt_elem, sizeof(char*));
    for (int i = 0; i < cnt_elem; ++i) {
        new_text[i] = text[i];
    }
    return new_text;
}

//==========================================================================
//! Frees memory carefully
//!
//! \param [in]     str         first array[][]
//! \param [in]     copied_str  second array[][]
//! \param [in]     size        size of array
//==========================================================================
void Free(char** str, char** copied_str, const int size) {
    for (int i = 0; i < size; ++i) {
        free(str[i]);
    }
    free(str);
    free(copied_str);
}


//==========================================================================
//! Reverses array[]
//!
//! \param [in]     str     original array
//! \param [in]     size    size of array
//! \return new array[], which is equal
//!                      to reversed original array
//==========================================================================
char* Reverse(char* str, const int size) {
    char* reverse_str = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; ++i) {
        reverse_str[size - i - 1] = str[i];
    }
    return reverse_str;
}





//==========================================================================
//! Sorts the array by the method
//!         of the quick sort algorithm
//!
//! \param [in]     base    array, which will be sorted
//! \param [in]     num     number of elements in array
//! \param [in]     size    size of every element in array in bytes
//! \param [in]     cmp     comparator
//!
//! P.S. asymptotics - O(N * log(N)), memory - O(size)
//==========================================================================
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