#include "commands.h"


int main() {
//    const char asm_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/asm.txt";
//    const char code_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/code.txt";
    const char asm_file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Processor/asm.txt";
    const char code_file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Processor/code.bin";

    assert(-1 != getCode(asm_file_name, /*makeOutName(file_name)*/code_file_name));

//    const char new_asm_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/new_asm.txt";

    const char new_asm_file_name[] = "/Users/avborovets/Desktop/PROGA/COMPILER-TECHNOLOGIES-AND-PROFFESIONAL-PROGRAMMING/Compiler-technologies-and-professional-programming/Processor/new_asm.txt";

//    const char code_file_name[] = "/Users/andrew_borovets/Desktop/proga/DED/Compiler-technologies-and-professional-programming/Processor/code.txt";

//    assert(-1 != getAsm(new_asm_file_name, code_file_name));

    return 0;
}