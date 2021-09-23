#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <sys/stat.h>

const int MAX_LENGTH = 256;
char* text;


void PrintSeparation();
void Print(char* text, int cnt_lines, int *indexes);
void PrintBeginning(const char* string);
void PrintEnd(const char* string);

int comp (const void* a, const void* b);
int reverse_comp(const void* a, const void* b);

char* ParseFileToArray(const char *file_name, const int cnt_lines, const int file_size, int *indexes);

int getCntLines(const char* file_name);
int getFileSize(const char* file_name);
int* Copy(int* indexes, const int cnt_elem);
char* Reverse(char* str, const int size);

void MyQiuckSort(int* base, size_t num, size_t size, int (*cmp) (const void *, const void *));





int main() {
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
    int cnt_lines = getCntLines(file_name);
    int file_size = getFileSize(file_name);

    printf("lines = %d, size = %d\n\n", cnt_lines, file_size);

    int* indexes = (int*) calloc(cnt_lines, sizeof(int));
    text = ParseFileToArray(file_name, cnt_lines, file_size, indexes);


    int* sorted_indexes = Copy(indexes, cnt_lines);
    qsort(sorted_indexes, cnt_lines, sizeof(int), comp);
    PrintBeginning("Sorted 'Hamlet' by the beginning of the lines:");
    Print(text, cnt_lines, sorted_indexes);
    PrintEnd("");
    PrintSeparation();

    MyQiuckSort(sorted_indexes, cnt_lines, sizeof(int), reverse_comp);
    PrintBeginning("Sorted 'Hamlet' by the end of the lines:");
    Print(text, cnt_lines, sorted_indexes);
    PrintEnd("");
    PrintSeparation();

    PrintBeginning("Original Hamlet");
    Print(text, cnt_lines, indexes);
    PrintEnd("");


    free(indexes);
    free(sorted_indexes);
    free(text);
    return 0;
}

void PrintEnd(const char* string) {
    printf("%s\n", string);
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/end.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
    int cnt_lines = getCntLines(file_name);
    int file_size = getFileSize(file_name);
    int* indexes = (int*) calloc(cnt_lines, sizeof(int));
    char* beginning = ParseFileToArray(file_name, cnt_lines, file_size, indexes);
    Print(beginning, cnt_lines, indexes);

    free(indexes);
}

void PrintBeginning(const char* string) {
    printf("%s\n", string);
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
//    const char file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
    int cnt_lines = getCntLines(file_name);
    int file_size = getFileSize(file_name);
    int* indexes = (int*) calloc(cnt_lines, sizeof(int));
    char* beginning = ParseFileToArray(file_name, cnt_lines, file_size, indexes);
    Print(beginning, cnt_lines, indexes);

    free(indexes);
}

void PrintSeparation() {
    printf("\n\n\n===========================================================================================\n\n\n");
}

//==========================================================================
//! Prints text
//!
//! \param [int]    text
//! \param [in]     cnt_lines   count of elements(lines) in text
//! \param [in]     indexes     array, where displacements
//!                                 from beginning of text are saved
//==========================================================================
void Print(char* text, int cnt_lines, int* indexes) {
    for (int i = 0; i < cnt_lines; ++i) {
        printf("%s", text + indexes[i]);
    }
}



int comp (const void* a, const void* b) {
    return strcmp(text + *(int*)a,text + *(int*)b);
}


int reverse_comp(const void* a, const void* b) {
    int first = *(int*)a;
    int second = *(int*)b;
    int size_first = strlen(text + first);
    int size_second = strlen(text + second);
    char* reverse_first = Reverse(text + first, size_first);
    char* reverse_second = Reverse(text + second, size_second);
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
//! \param [in]     file_size       size of file
//! \param [in]     indexes         array, where displacements
//!                                     from beginning of text are saved
//! \return ptr to text
//!
//! P.S. after this function indexes will be filled
//==========================================================================
char* ParseFileToArray(const char* file_name, const int cnt_lines, const int file_size, int* indexes) {

    char* text = (char*) calloc(file_size + cnt_lines + 1, sizeof(char));

    FILE* file = fopen(file_name,"r");

    if(file == NULL) {
        printf("can not open file '%s'", file_name);
        return NULL;
    }

    char* cur_ptr = text;
    int ind_line = 0;
    while(!feof (file)) {
        if (fgets(cur_ptr, MAX_LENGTH, file)) {
            indexes[ind_line] = cur_ptr - text;
            cur_ptr = strchr(cur_ptr, '\0') + 1;
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
//! Finds size of file
//!
//! \param file_name    name of file
//! \return size of file in bytes
//==========================================================================
int getFileSize(const char* file_name) {
    struct stat st;
    stat(file_name, &st);
    return st.st_size;
}

//==========================================================================
//! Copies array[] to a new_array[]
//!
//! \param [in]     indexes     original array
//! \param [in]     cnt_elem    count of elements in array
//! \return new_array[]
//==========================================================================
int* Copy(int* indexes, const int cnt_elem) {
    int* new_indexes = (int*) calloc(cnt_elem, sizeof(int));
    for (int i = 0; i < cnt_elem; ++i) {
        new_indexes[i] = indexes[i];
    }
    return new_indexes;
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
void MyQiuckSort(int* base, size_t num, size_t size, int (*cmp)(const void *, const void *)) {
    int first = 0;
    int last = num - 1;
    int* array = base;
    if (first < last)
    {
        int left = first, right = last, middle = (left + right) / 2;
        do
        {
            while (cmp(&array[left], &array[middle]) < 0) {
                ++left;
            }
            while (cmp(&array[right], &array[middle]) > 0) {
                --right;
            }
            if (left <= right)
            {
                int tmp = array[left];
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