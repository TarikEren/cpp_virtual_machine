#ifndef CPP_VIRTUAL_MACHINE_LEXER_H
#define CPP_VIRTUAL_MACHINE_LEXER_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "errors.h"
#include "logger.h"

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

    //Constructor
    explicit Lexer() = default;

    void set_file_text(const std::string& text);

    //Iterates through the file_text variable and creates tokens.
    void tokenize();

    //Moves one character forward in the file_text variable.
    void advance();

    //Adds the current character to the buffer.
    void buffer_add();

    //Clears the buffer.
    void buffer_clear();

    //Checks if the file_text variable is full.
    bool is_file_text_full() {
        if (file_text.empty()) return false;
        return true;
    }

    //Returns the parsed instructions.
    std::vector<std::string> get_instructions() {
        return this->instructions;
    }
};


#endif
