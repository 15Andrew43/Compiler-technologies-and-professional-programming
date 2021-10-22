#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <cstring>


const int MAX_LENGTH = 256;
const size_t n_cmds = 7;
const size_t len_cmd = 10;
const size_t len_int = 32;



void PrintDigit(FILE* out_file, int i) {
    char int_str[len_int];
    snprintf(int_str, len_int, "%d", i);
    fwrite(int_str, sizeof(char), strlen(int_str), out_file);
}

void PrintSep(FILE* out_file, const char* sep) {
    fwrite(sep, sizeof(char), strlen(sep), out_file);
}

void pushF(const char* text, FILE* out_file, int i) {
    char cmd[len_cmd];
    int digit = -1;
    sscanf(text, "%s %d", cmd, &digit);

    PrintDigit(out_file, i);
    PrintSep(out_file, " ");
    PrintDigit(out_file, digit);
    PrintSep(out_file, "\n");
}

void popF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void addF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void subF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void mulF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void outF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}

void htlF(const char* text, FILE* out_file, int i) {
    PrintDigit(out_file, i);
    PrintSep(out_file, "\n");
}





struct Commands {
    FILE* in_file = NULL;
    FILE* out_file = NULL;

    char cmds[n_cmds][len_cmd] = {
            "push",
            "pop",
            "add",
            "sub",
            "mul",
            "out",
            "hlt"
    };
    void (*cmdsF[n_cmds]) (const char* text, FILE* out_file, int i) = {
            pushF,
            popF,
            addF,
            subF,
            mulF,
            outF,
            htlF,
    };
};



void DoCmd(const char* text, const Commands &commands, char *cmd) {
    FILE* in_file = commands.in_file;
    FILE* out_file = commands.out_file;

    for (int i = 0; i < n_cmds; ++i) {
        if (strcmp(cmd, commands.cmds[i]) == 0) {

            commands.cmdsF[i](text, out_file, i);
            break;
        }
    }
}

int getAsm(const char* file_name, const char* out_name) {

    FILE* in_file = fopen(file_name, "r");
    if (in_file == NULL) {
        return -1;
    }
    FILE* out_file = fopen(out_name, "w");
    if (out_file == NULL) {
        return -1;
    }

    Commands commands{in_file, out_file};

    char* text = (char*) calloc(MAX_LENGTH, sizeof(char));
    char* cmd = (char*) calloc(len_cmd, sizeof(char));

    while(!feof (in_file)) {
        if (fgets(text, MAX_LENGTH, in_file)) {
            sscanf(text, "%s", cmd);
            DoCmd(text, commands, cmd);
        }
    }

    free(text);
    free(cmd);
    fclose(in_file);
    fclose(out_file);
}

int main() {
    const char file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/in.txt";

    assert(-1 != getAsm(file_name, /*makeOutName(file_name)*/"/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/code_out.txt"));

    return 0;
}