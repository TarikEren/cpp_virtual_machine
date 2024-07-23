#include <cstring>
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

int main(int argc, char* argv[]) {
    Machine machine;
    if (argc == 1) {
        printf("ERROR: No file provided\n");
        exit(NO_TARGET_FILE_PROVIDED);
    }
    std::string filename = argv[1];
    char ext[5] = {filename[filename.size() - 4], filename[filename.size() - 3], filename[filename.size() - 2], filename[filename.size() - 1], '\0'};
    if (strcmp(ext, "basm") != 0) {
        printf("ERROR: Invalid file extension\n");
        exit(INVALID_FILE_EXT);
    }
    Lexer lexer(filename);
    lexer.tokenize();
    std::vector<std::string> instructions = lexer.get_instructions();
    word hex;
    for (int i = int(instructions.size()-1); i > -1; i--) {
        std::string current = instructions[i];
        hex = string_to_hex(current);
        machine.push(string_to_hex(current));
    }
    machine.execute();
}