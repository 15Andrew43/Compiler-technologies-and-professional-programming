#include "commands.h"


void PrintDigit(FILE* out_file, int i) {
    char int_str[len_int];
    snprintf(int_str, len_int, "%d", i);
    fwrite(int_str, sizeof(char), strlen(int_str), out_file);
}

void PrintSep(FILE* out_file, const char* sep) {
    fwrite(sep, sizeof(char), strlen(sep), out_file);
}

void pushAsm(const Commands &commands, const char* text, FILE* out_file) {
    char cmd[len_cmd];
    sscanf(text, "%s", cmd);
    int len = strlen(cmd);
    int offset = FindSymb(text, len);


    int ok = -1;
    char ch = 0;
    int digit = 0;

    char tmp_ch = 0;
    int tmp_digit = 0;
    unsigned char number_cmd = 0;
    bool flag = true;

    sscanf(text + offset, "%d%n", &tmp_digit, &ok);
    if (ok == 1) {
        ch = tmp_ch;
        digit = tmp_digit;
        number_cmd |= 0;
        number_cmd |= 32;
    }
    sscanf(text + offset, "%cx%n", &tmp_ch, &ok);
    if (ok == 2) {
        ch = tmp_ch;
        digit = tmp_digit;
        ch -= 'a';
        number_cmd |= 0;
        number_cmd |= 64;
    }
    sscanf(text + offset, "%cx+%d%n", &tmp_ch, &tmp_digit, &ok);
    if (ok == 4) {
        flag = false;
        ch = tmp_ch;
        digit = tmp_digit;
        ch -= 'a';
        number_cmd |= 0;
        number_cmd |= 32;
        number_cmd |= 64;
    }
    sscanf(text + offset, "[%d]%n", &tmp_digit, &ok);
    if (ok == 3) {
        ch = tmp_ch;
        digit = tmp_digit;
        number_cmd |= 0;
        number_cmd |= 32;
        number_cmd |= 128;
    }
    sscanf(text + offset, "[%cx]%n", &tmp_ch, &ok);
    if (ok == 4 && flag) {
        ch = tmp_ch;
        digit = tmp_digit;
        ch -= 'a';
        number_cmd |= 0;
        number_cmd |= 64;
        number_cmd |= 128;
    }
    sscanf(text + offset, "[%cx+%d]%n", &tmp_ch, &tmp_digit, &ok);
    if (ok == 6) {
        ch = tmp_ch;
        digit = tmp_digit;
        ch -= 'a';
        number_cmd |= 0;
        number_cmd |= 32;
        number_cmd |= 64;
        number_cmd |= 128;
    }
    fwrite(&number_cmd, sizeof(char), 1, out_file);
    if ((number_cmd & 32) == 32) {
        fwrite(&digit, sizeof(int), 1, out_file);
    }
    if ((number_cmd & 64) == 64) {
        fwrite(&ch, sizeof(char), 1, out_file);
    }

}

int FindSymb(const char *text, int len) {
    for (int i = len; text[i] != '\0'; ++i) {
        if (text[i] != ' ' && text[i] != '\t') {
            return i;
        }
    }
    return 0;
}

void popAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 1;

    char cmd[len_cmd];
    sscanf(text, "%s", cmd);
    int len = strlen(cmd);
    int offset = FindSymb(text, len);

    if (offset != 0) {
        int ok = -1;
        char ch = 0;

        sscanf(text + offset, "%cx%n", &ch, &ok);
        if (ok == 1) {
            number_cmd |= 64;
        }
    }
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

void addAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 2;
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

void subAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 3;
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

void mulAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 4;
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

void outAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 5;
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

void htlAsm(const Commands &commands, const char* text, FILE* out_file) {
    unsigned char number_cmd = 0;
    number_cmd |= 6;
    fwrite(&number_cmd, sizeof(char), 1, out_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void PrintStr(FILE *out_file, const char* str) {
    fwrite(str, sizeof(char), strlen(str), out_file);
}

void pushDisasm(const Commands &commands, const char *text, FILE *out_file) {
    int cmd;
    char digit[len_int];
    sscanf(text, "%d %s", &cmd, digit);

    PrintStr(out_file, commands.cmds[0]);
    PrintSep(out_file, " ");
    PrintStr(out_file, digit);
    PrintSep(out_file, "\n");
}

void popDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[1]);
    PrintSep(out_file, "\n");
}

void addDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[2]);
    PrintSep(out_file, "\n");
}

void subDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[3]);
    PrintSep(out_file, "\n");
}

void mulDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[4]);
    PrintSep(out_file, "\n");
}

void outDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[5]);
    PrintSep(out_file, "\n");
}

void htlDisasm(const Commands &commands, const char* text, FILE* out_file) {
    PrintStr(out_file, commands.cmds[6]);
    PrintSep(out_file, "\n");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void DoCmdFromAsm(const char* text, const Commands &commands, char *cmd) {
    FILE* asm_file = commands.asm_file;
    FILE* code_file = commands.code_file;

    for (int i = 0; i < n_cmds; ++i) {
        if (strcmp(cmd, commands.cmds[i]) == 0) {
            commands.cmdsAsm[i](commands, text, code_file);
            break;
        }
    }
}

void DoCmdFromCode(char *text, Commands commands, int cmd) {
    FILE* asm_file = commands.asm_file;
    FILE* code_file = commands.code_file;

    commands.cmdsDisasm[cmd](commands, text, asm_file);
}

int getAsm(const char* asm_file_name, const char* code_file_name) {
    FILE* asm_file = fopen(asm_file_name, "w");
    if (asm_file == NULL) {
        return -1;
    }
    FILE* code_file = fopen(code_file_name, "r");
    if (code_file == NULL) {
        return -1;
    }

    Commands commands{asm_file, code_file};

    char* text = (char*) calloc(MAX_LENGTH, sizeof(char));
    int cmd;

    while(!feof (code_file)) {
        if (fgets(text, MAX_LENGTH, code_file)) {
            sscanf(text, "%d", &cmd);
            DoCmdFromCode(text, commands, cmd);
        }
    }

    free(text);
    fclose(asm_file);
    fclose(code_file);
    return 0;
}

int getCode(const char* asm_file_name, const char* code_file_name) {

    FILE* asm_file = fopen(asm_file_name, "r");
    if (asm_file == NULL) {
        return -1;
    }
    FILE* code_file = fopen(code_file_name, "wb");
    if (code_file == NULL) {
        return -1;
    }

    Commands commands{asm_file, code_file};

    char* text = (char*) calloc(MAX_LENGTH, sizeof(char));
    char* cmd = (char*) calloc(len_cmd, sizeof(char));

    while(!feof (asm_file)) {
        if (fgets(text, MAX_LENGTH, asm_file)) {
            sscanf(text, "%s", cmd);
            DoCmdFromAsm(text, commands, cmd);
        }
    }

    free(text);
    free(cmd);
    fclose(asm_file);
    fclose(code_file);

    return Ok;
}




Error DoCPU(const char *code_file_name) {
    CPU cpu = CPUConstructor(code_file_name, RAMSize);

    Error error = WorkCPU(&cpu);

    CPUDestuctor(&cpu);
    return Ok;
}

Error WorkCPU(CPU *ptr_cpu) {
    Stack stack = ptr_cpu->stack;
    Code code = ptr_cpu->code;
    int* RAM = (int*) ptr_cpu->RAM;
    int* registers = ptr_cpu->resisters;

    Commands cmds;

    while (ptr_cpu->ip < ptr_cpu->code.size) {
        int cmd = code.code[ptr_cpu->ip];
        Error error = cmds.cmdsCPU[cmd](ptr_cpu);
        if (error == htl) {
            return htl;
        }
    }

    return Ok;
}



CPU CPUConstructor(const char *code_file_name, const size_t RAMSize) {
    CPU cpu = {};
    cpu.stack = StackConstructor("stack");
    Code code = ReadCode(code_file_name);
    assert(code.code != NULL);
    cpu.code = code;
//    PrintArray(code.code, code.size);
    cpu.ip = 0;
    cpu.RAM = (int*) calloc(RAMSize, sizeof(int));
    return cpu;
}



Error CPUDestuctor(CPU *ptr_cpu) {
    StackDestructor(&ptr_cpu->stack);
    free(ptr_cpu->code.code);
    free(ptr_cpu->RAM);
    return Ok;
}



void PrintArray(int *array, size_t size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
}


Code ReadCode(const char *code_file_name) {

    FILE* file = fopen(code_file_name, "r");
    if (file == NULL) {
        printf("can't open file %s\n", code_file_name);
        return {NULL, 0};
    }

    size_t cnt_cmds = getCntCmds(file);

    fseek(file, 0, SEEK_SET);

    int* code = (int*) calloc(cnt_cmds, sizeof(int));
    int cmd = -1;
    int ip = 0;

    while(!feof (file)) {
        if (fscanf(file, "%d", &cmd)) {
            code[ip++] = cmd;
        }
    }

    fclose(file);

    return {code, cnt_cmds};
}



int getCntCmds(FILE *file) {
    fseek(file , 0, SEEK_SET);

    int cmd = -1;
    int cnt_cmds = 0;

    while(!feof (file)) {
        if (fscanf(file, "%d", &cmd)) {
            ++cnt_cmds;
        }
    }

    return cnt_cmds;
}



Error pushCPU(CPU* ptr_cpu) {
    StackPush(&(ptr_cpu->stack), ptr_cpu->code.code[ptr_cpu->ip + 1]);
    ptr_cpu->ip += 2;
    return Ok;
}

Error popCPU(CPU* ptr_cpu) {
    int elem = -1;
    StackPop(&(ptr_cpu->stack), &elem);
    ptr_cpu->ip += 1;
    return Ok;
}

Error addCPU(CPU* ptr_cpu) {
    int prev = -1;
    int prev_prev = -1;
    StackPop(&(ptr_cpu->stack), &prev);
    StackPop(&(ptr_cpu->stack), &prev_prev);
    StackPush(&(ptr_cpu->stack), prev_prev + prev);
    ptr_cpu->ip += 1;
    return Ok;
}

Error subCPU(CPU* ptr_cpu) {
    int prev = -1;
    int prev_prev = -1;
    StackPop(&(ptr_cpu->stack), &prev);
    StackPop(&(ptr_cpu->stack), &prev_prev);
    StackPush(&(ptr_cpu->stack), prev_prev - prev);
    ptr_cpu->ip += 1;
    return Ok;
}

Error mulCPU(CPU* ptr_cpu) {
    int prev = -1;
    int prev_prev = -1;
    StackPop(&(ptr_cpu->stack), &prev);
    StackPop(&(ptr_cpu->stack), &prev_prev);
    StackPush(&(ptr_cpu->stack), prev_prev * prev);
    ptr_cpu->ip += 1;
    return Ok;
}

Error outCPU(CPU* ptr_cpu) {
    while (ptr_cpu->stack.size > 0) {
        int prev = -1;
        StackPop(&(ptr_cpu->stack), &prev);
        printf("%d ", prev);
    }
    ptr_cpu->ip += 1;
    return Ok;
}

Error htlCPU(CPU* ptr_cpu) {
    return htl;
}
