#ifndef CPP_VIRTUAL_MACHINE_LEXER_H
#define CPP_VIRTUAL_MACHINE_LEXER_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "errors.h"

class Lexer {
private:
    char current{};
    std::string file_text{}, buffer{};
    size_t index{};
    std::vector<std::string> instructions{};
public:
    //Constructor
    //Initialises values.
    //Takes a file_name argument and reads target file using ifstream.
    explicit Lexer(const std::string& file_name);

    //Iterates through the file_text variable and creates tokens.
    void tokenize();

    //Prints the file_text value.
    //Used for debugging/checking whether the file has been read properly or not.
    void print_file_text();

    //Prints the instructions.
    void print_instructions();

    //Checks the next character and returns it.
    char peek();

    //Moves one character forward in the file_text variable.
    void advance();

    //Moves back one character in file_text variable.
    void step_back();

    //Adds the current character to the buffer.
    void buffer_add();

    //Clears the buffer.
    void buffer_clear();

    std::vector<std::string> get_instructions() {
        return this->instructions;
    }
};


#endif
