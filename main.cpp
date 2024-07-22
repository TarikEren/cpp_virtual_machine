#include "headers/machine.h"
#include "headers/lexer.h"

/*
 * ADD  1XXX
 * SUB  2XXX
 * SAVE 3XXX
 * LOAD 4XXX
 * INT  5XXX
*/

word string_to_hex(std::string& str) {
    str = str.substr(1);
    std::stringstream hex_stream;
    hex_stream << std::hex << str;
    word result;
    hex_stream >> result;
    return result;
}

int main() {
    Machine machine;
    Lexer lexer("test.txt"); //TODO: Change this to argv[1] on release.
    lexer.tokenize();
    std::vector<std::string> instructions = lexer.get_instructions();
    word hex;
    for (int i = int(instructions.size()-1); i > -1; i--) {
        std::string current = instructions[i];
        hex = string_to_hex(current);
        machine.push(string_to_hex(current));
    }
    machine.execute();
    machine.dump_stack();
}