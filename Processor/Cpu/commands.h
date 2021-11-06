#ifndef CPU_COMMANDS_H
#define CPU_COMMANDS_H


#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <cstring>

#include "stack.h"





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





const size_t RAMSize = 1024; // bytes
const size_t MaxCodeSize = 1000;

enum Error {
    Ok = 0,

};


struct Code {
    int* code;
    size_t size;
};

struct CPU {
    Stack stack;
    Code code;
    int ip = 0;
    int resisters[4];
    void* RAM;
};


Error DoCPU(const char *code_file_name);

CPU CPUConstructor(const char *code_file_name, const size_t RAMSize);

Error CPUDestuctor(CPU *ptr_cpu);

Code ReadCode(const char *code_file_name);

int getCntCmds(FILE *file);



void PrintArray(int *array, size_t size);

Error WorkCPU(CPU *ptr_cpu);




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










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
    CPU cpu;
//    void (*cmdsCPU[n_cmds]) (CPU* cpu) = {
////            pushCPU,
////            popCPU,
////            addCPU,
////            subCPU,
////            mulCPU,
////            outCPU,
////            htlCPU,
//    };
};


void PrintDigit(FILE* out_file, int i);
void PrintSep(FILE* out_file, const char* sep);
void PrintStr(FILE *out_file, const char* str);


void DoCmdFromAsm(const char* text, const Commands &commands, char *cmd);

void DoCmdFromCode(char *text, Commands commands, int cmd);

int getAsm(const char* asm_file_name, const char* code_file_name);

int getCode(const char* asm_file_name, const char* code_file_name);













#endif //CPU_COMMANDS_H
