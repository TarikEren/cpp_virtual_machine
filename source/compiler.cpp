#include "../headers/compiler.h"

void Compiler::compile(Lexer lexer) {
    Machine machine;
    lexer.tokenize();
    std::vector<std::string> instructions = lexer.get_instructions();
    for (int i = int(instructions.size()-1); i > -1; i--) {
        std::string current = instructions[i];
        machine.push(Lexer::string_to_hex(current));
    }
    machine.execute();
}