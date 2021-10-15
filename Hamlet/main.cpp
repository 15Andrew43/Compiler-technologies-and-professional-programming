#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <sys/stat.h>

const int MAX_LENGTH = 256;



struct TextElem {
    char* text = NULL;
    long long int offset = 0;
};



void PrintSeparation(FILE *file);
void Print(const char *text, const int cnt_lines, TextElem *indexes, FILE *file);
void PrintBeginning(const char *string, FILE *file_out, FILE *file_in);
void PrintEnd(const char *string, FILE *file_out, FILE *file_in);

int comp (const void* a, const void* b);
int reverse_comp(const void* a, const void* b);

char *ParseFileToArray(FILE *file, const int cnt_lines, const int file_size, TextElem *indexes);

int getCntLines(FILE *file);
int getFileSize(FILE *file);
TextElem * Copy(TextElem *indexes, const int cnt_elem);
char* Reverse(char* str, const int size);
int FindLetter(const char* str);

void MyQiuckSort(TextElem *base, size_t num, size_t size, int (*cmp) (const void *, const void *));




int main() {
    const char file_out_name[]   = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/out.txt";
    const char file_in_name[]    = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/hamlet.txt";
    const char file_begin_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/beginning.txt";
    const char file_end_name[]   = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Hamlet/end.txt";

    FILE* file_out = fopen(file_out_name, "w+");
    if (file_out == NULL) {
        printf("can not open file '%s'", file_out_name);
        return -1;
    }
    FILE* file_in = fopen(file_in_name, "r");
    if (file_in == NULL) {
        printf("can not open file '%s'", file_in_name);
        return -1;
    }

    FILE* file_begin = fopen(file_begin_name, "r");
    if (file_begin == NULL) {
        printf("can not open file '%s'", file_begin_name);
        return -1;
    }
    FILE* file_end = fopen(file_end_name, "r");
    if (file_end == NULL) {
        printf("can not open file '%s'", file_end_name);
        return -1;
    }


    int cnt_lines = getCntLines(file_in);
    int file_size = getFileSize(file_in);


    TextElem* text_elems = (TextElem*) calloc(cnt_lines, sizeof(TextElem));
    char* text = ParseFileToArray(file_in, cnt_lines, file_size, text_elems);


    TextElem* sorted_indexes = Copy(text_elems, cnt_lines);

    qsort(sorted_indexes, cnt_lines, sizeof(TextElem), comp);

    PrintBeginning("Sorted 'Hamlet' by the beginning of the lines:\n", file_out, file_begin);
    Print(text, cnt_lines, sorted_indexes, file_out);
    PrintEnd("\n", file_out, file_end);
    PrintSeparation(file_out);

    MyQiuckSort(sorted_indexes, cnt_lines, sizeof(TextElem), reverse_comp);
    PrintBeginning("Sorted 'Hamlet' by the end of the lines:\n", file_out, file_begin);
    Print(text, cnt_lines, sorted_indexes, file_out);
    PrintEnd("\n", file_out, file_end);
    PrintSeparation(file_out);

    PrintBeginning("Original Hamlet\n", file_out, file_begin);
    Print(text, cnt_lines, text_elems, file_out);
    PrintEnd("\n", file_out, file_end);


    free(text_elems);
    free(sorted_indexes);
    free(text);
    return 0;
}




void PrintEnd(const char *string, FILE *file_out, FILE *file_in) {
    fseek(file_out, 0, SEEK_END);

    fwrite(string, sizeof(char), strlen(string), file_out);

    int cnt_lines = getCntLines(file_in);
    int file_size = getFileSize(file_in);
    TextElem* indexes = (TextElem*) calloc(cnt_lines, sizeof(TextElem));
    char* beginning = ParseFileToArray(file_in, cnt_lines, file_size, indexes);
    Print(beginning, cnt_lines, indexes, file_out);

    free(indexes);
}

void PrintBeginning(const char *string, FILE *file_out, FILE *file_in) {
    fseek(file_out, 0, SEEK_END);

    fwrite(string, sizeof(char), strlen(string), file_out);

    int cnt_lines = getCntLines(file_in);
    int file_size = getFileSize(file_in);
    TextElem* indexes = (TextElem*) calloc(cnt_lines, sizeof(TextElem));
    char* beginning = ParseFileToArray(file_in, cnt_lines, file_size, indexes);
    Print(beginning, cnt_lines, indexes, file_out);

    free(indexes);
}

void PrintSeparation(FILE *file) {
    fseek(file, 0, SEEK_END);

    const char sep[] = "\n\n\n===========================================================================================\n\n\n";
    fwrite(sep, sizeof(char), strlen(sep), file);
}

//==========================================================================
//! Prints text
//!
//! \param [int]    text
//! \param [in]     cnt_lines   count of elements(lines) in text
//! \param [in]     indexes     array, where displacements
//!                                 from beginning of text are saved
//==========================================================================
void Print(const char *some_text, const int cnt_lines, TextElem *indexes, FILE *file) {
    fseek(file, 0, SEEK_END);

    char* text = indexes[0].text;

    for (int i = 0; i < cnt_lines; ++i) {
        fwrite(text + indexes[i].offset, sizeof(char), strlen(some_text + indexes[i].offset), file);
    }
}



int comp (const void* a, const void* b) {
    char* text = (*(TextElem*)a).text;
    long offset_a = (*(TextElem*)a).offset;
    long offset_b = (*(TextElem*)b).offset;

    return strcmp(text + offset_a, text + offset_b);
}


int reverse_comp(const void* a, const void* b) {
    char* text = (*(TextElem*)a).text;
    int offset_a = (*(TextElem*)a).offset;
    int offset_b = (*(TextElem*)b).offset;

    int size_a = strlen(text + offset_a);
    int size_b = strlen(text + offset_b);
    char* reverse_a = Reverse(text + offset_a, size_a);
    char* reverse_b = Reverse(text + offset_b, size_b);

    int displ_a = FindLetter(reverse_a);
    int displ_b = FindLetter(reverse_b);

    int res_cmp = strcmp(reverse_a + displ_a, reverse_b + displ_b);
    free(reverse_a);
    free(reverse_b);
    return res_cmp;
}

int FindLetter(const char* str) {
    int ind = 0;
    while (str[ind] != '\0') {
        if ((str[ind] >= 65 && str[ind] <= 90)
            || (str[ind] >= 97 && str[ind] <= 122)) {
            return ind;
        }
        ++ind;
    }
    return 0;
}


//==========================================================================
//! Opens file, reads it line by line
//!             and save every line to dynamic memory
//!
//! \param [in]     file            FILE* which show on necessary file
//! \param [in]     cnt_lines       count of lines in file
//! \param [in]     file_size       size of file
//! \param [in]     indexes         array, where displacements
//!                                     from beginning of text are saved
//! \return ptr to text
//!
//! P.S. after this function indexes will be filled
//==========================================================================
char *ParseFileToArray(FILE *file, const int cnt_lines, const int file_size, TextElem *indexes) {
    fseek(file, 0, SEEK_SET);

    char* text = (char*) calloc(file_size + cnt_lines + 1, sizeof(char));


    char* cur_ptr = text;
    int ind_line = 0;
    while(!feof (file)) {
        if (fgets(cur_ptr, MAX_LENGTH, file)) {
            int pep = cur_ptr - text;
            TextElem ele = {text, pep};
            indexes[ind_line] = ele;

            cur_ptr = strchr(cur_ptr, '\0') + 1;
            ++ind_line;
        }
    }

    return text;
}


//==========================================================================
//! Counts number of lines in file
//!
//! \param [in]     file    FILE* which show on necessary file
//! \return number of lines in file
//==========================================================================
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

//==========================================================================
//! Finds size of file
//!
//! \param      file    FILE* which show on necessary file
//! \return size of file in bytes
//==========================================================================
int getFileSize(FILE *file) {
    struct stat st;

    if ((fstat(fileno(file), &st) != 0) || (!S_ISREG(st.st_mode))) {
        return -1;
    }

    return st.st_size;
}

//==========================================================================
//! Copies array[] to a new_array[]
//!
//! \param [in]     indexes     original array
//! \param [in]     cnt_elem    count of elements in array
//! \return new_array[]
//==========================================================================
TextElem * Copy(TextElem *indexes, const int cnt_elem) {
    TextElem* new_indexes = (TextElem*) calloc(cnt_elem, sizeof(TextElem));
    for (int i = 0; i < cnt_elem; ++i) {

        new_indexes[i] = indexes[i];
        TextElem lol = indexes[i];
        TextElem lollol = new_indexes[i];
        int l = 345;

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
    char* reverse_str = (char*) calloc(size + 1, sizeof(char));
    for (int i = 0; i < size; ++i) {
        reverse_str[size - i - 1] = str[i];
    }
    reverse_str[size] = '\0';
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
void MyQiuckSort(TextElem *base, size_t num, size_t size, int (*cmp)(const void *, const void *)) {
    int first = 0;
    int last = num - 1;
    TextElem* array = base;
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
                TextElem tmp = array[left];
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