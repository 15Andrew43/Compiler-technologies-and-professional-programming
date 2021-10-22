#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <cstring>


const int MAX_LENGTH = 256;
const size_t n_cmds = 7;
const size_t len_cmd = 10;
const size_t len_int = 32;

struct Commands;

void pushAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void popAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void addAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void subAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void mulAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void outAsm(const Commands &commands, const char* text, FILE* out_file, int i);
void htlAsm(const Commands &commands, const char* text, FILE* out_file, int i);

void pushDisasm(const Commands &commands, const char *text, FILE *out_file, int i);
void popDisasm(const Commands &commands, const char* text, FILE* out_file, int i);
void addDisasm(const Commands &commands, const char* text, FILE* out_file, int i);
void subDisasm(const Commands &commands, const char* text, FILE* out_file, int i);
void mulDisasm(const Commands &commands, const char* text, FILE* out_file, int i);
void outDisasm(const Commands &commands, const char* text, FILE* out_file, int i);
void htlDisasm(const Commands &commands, const char* text, FILE* out_file, int i);




struct Commands {
    FILE* asm_file = NULL;
    FILE* code_file = NULL;

    char cmds[n_cmds][len_cmd] = {
            "push",
            "pop",
            "add",
            "sub",
            "mul",
            "out",
            "hlt"
    };
    void (*cmdsAsm[n_cmds]) (const Commands &commands, const char* text, FILE* out_file, int i) = {
            pushAsm,
            popAsm,
            addAsm,
            subAsm,
            mulAsm,
            outAsm,
            htlAsm,
    };
    void (*cmdsDisasm[n_cmds]) (const Commands &commands, const char* text, FILE* out_file, int i) = {
            pushDisasm,
            popDisasm,
            addDisasm,
            subDisasm,
            mulDisasm,
            outDisasm,
            htlDisasm,
    };
};


void PrintDigit(FILE* out_file, int i) {
    char int_str[len_int];
    snprintf(int_str, len_int, "%d", i);
    fwrite(int_str, sizeof(char), strlen(int_str), out_file);
}

void PrintSep(FILE* out_file, const char* sep) {
    fwrite(sep, sizeof(char), strlen(sep), out_file);
}

void pushAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    char cmd[len_cmd];
    int digit = -1;
    sscanf(text, "%s %d", cmd, &digit);

    PrintDigit(out_file, i);
    PrintSep(out_file, " ");
    PrintDigit(out_file, digit);
    PrintSep(out_file, "\n");
}

void popAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void addAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void subAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void mulAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void outAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void htlAsm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

////////////////////////////////Xx/////////////////////////////////////


void PrintStr(FILE *out_file, const char* str) {
    fwrite(str, sizeof(char), strlen(str), out_file);
}

void pushDisasm(const Commands &commands, const char *text, FILE *out_file, int i) {
    int cmd;
    char digit[len_int];
    sscanf(text, "%d %s", &cmd, digit);

    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, " ");
    PrintStr(out_file, digit);
    PrintSep(out_file, "\n");
}

void popDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}

void addDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}

void subDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}

void mulDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}

void outDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}

void htlDisasm(const Commands &commands, const char* text, FILE* out_file, int i) {
    PrintStr(out_file, commands.cmds[i]);
    PrintSep(out_file, "\n");
}


/////////////////////////////////


void DoCmdFromAsm(const char* text, const Commands &commands, char *cmd) {
    FILE* asm_file = commands.asm_file;
    FILE* code_file = commands.code_file;

    for (int i = 0; i < n_cmds; ++i) {
        if (strcmp(cmd, commands.cmds[i]) == 0) {
            commands.cmdsAsm[i](commands, text, code_file, i);
            break;
        }
    }
}

void DoCmdFromCode(char *text, Commands commands, int cmd) {
    FILE* asm_file = commands.asm_file;
    FILE* code_file = commands.code_file;

    commands.cmdsDisasm[cmd](commands, text, asm_file, cmd);
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
    FILE* code_file = fopen(code_file_name, "w");
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
}

int main() {
    const char asm_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/asm.txt";
    const char code_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/code.txt";

    assert(-1 != getCode(asm_file_name, /*makeOutName(file_name)*/code_file_name));

    return 0;
}