#include "../headers/compiler.h"

word string_to_hex(std::string& str) {
    str = str.substr(1);
    std::stringstream hex_stream;
    hex_stream << std::hex << str;
    word result;
    hex_stream >> result;
    return result;
}


void Compiler::compile(const std::string& filename) {
    Machine machine;
    Lexer lexer(filename);
    if (!lexer.is_file_text_full()) return;
    lexer.tokenize();
    std::vector<std::string> instructions = lexer.get_instructions();
    word hex;
    for (int i = int(instructions.size()-1); i > -1; i--) {
        std::string current = instructions[i];
        hex = string_to_hex(current);
        machine.push(hex);
    }
    machine.execute();
}

void Compiler::compile(Lexer lexer) {
    Machine machine;
    lexer.tokenize();
    std::vector<std::string> instructions = lexer.get_instructions();
    word hex;
    for (int i = int(instructions.size()-1); i > -1; i--) {
        std::string current = instructions[i];
        hex = string_to_hex(current); //For some reason the program doesn't work properly when this line is removed.
        machine.push(string_to_hex(current));
    }
    machine.execute();
}
