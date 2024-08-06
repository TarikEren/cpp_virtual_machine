#ifndef CPP_VIRTUAL_MACHINE_LEXER_H
#define CPP_VIRTUAL_MACHINE_LEXER_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "errors.h"
#include "logger.h"
#include "definitions.h"

class Lexer {
private:
    char current{};
    std::string text{};
    size_t index{};
    std::vector<std::string> instructions{};
public:
    //Constructor
    explicit Lexer() = default;

    //Reads file and sets the text variable
    void read_file(const std::string&);

    //Sets the file_text variable
    void set_file_text(const std::string&);

    //Iterates through the text variable and creates tokens.
    void tokenize();

    //Returns the next character.
    char peek(int);

    //Moves one character forward in the text variable.
    void advance();

    //Returns the parsed instructions.
    std::vector<std::string> get_instructions() {
        return this->instructions;
    }

    //Transforms a string to a hex value
    static word string_to_hex(std::string&);

    //Checks if an operand is in bounds.
    static bool operand_in_bounds(std::string&);

    static bool char_is_hex(char);

    bool operand_exists(char);
};


#endif
