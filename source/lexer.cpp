#include "../headers/lexer.h"

void Lexer::read_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::string message = "Unable to open file " + file_name;
        logger(ERROR, message, FILE_NOT_FOUND);
        this->text = "";
        return;
    }
    std::stringstream stream_buffer;
    stream_buffer << file.rdbuf();
    this->text = stream_buffer.str();
}

void Lexer::advance() {
    this->index += 1;
    this->current = this->text[this->index];
}

void Lexer::tokenize() {
    //Instruction buffer for pushing onto instructions vector.
    std::string instruction{}, operand{}, buffer{};
    //Line and col for error handling.
    int line = 1, col = 1;
    this->index = 0;
    this->current = this->text[this->index];
    while (current != '\0') {
        while (isalnum(current)) {
            col += 1;
            //Push char onto buffer
            buffer.push_back(current);
            //Advance further
            advance();
            if (current == '\n' || current == ' ' || current == '\0') {
                //If INT instruction has been encountered
                if (buffer == "INT") {
                    //If an operand wasn't provided
                    if (!operand_exists(current)) {
                        printf("%s Missing operand at line: %d, col: %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    //Use the 0x5 prefix
                    instruction.append("0x5");
                    //Advance further
                    advance();
                    //Until the newline character
                    while (current != '\n') {
                        col += 1;
                        //If an invalid character was provided
                        if (!char_is_hex(current)) {
                            printf("%s Invalid char %c at line: %d, col: %d\n", error, current, line, col);
                            buffer.clear();
                            this->instructions.clear();
                            this->text.clear();
                            return;
                        }
                        //Push char onto buffer
                        operand.push_back(current);
                        //Advance further
                        advance();
                    }
                    line += 1;
                    col = 1;
                    //If the provided operand out of bounds
                    if (!operand_in_bounds(operand)) {
                        logger(FATAL_ERROR, "Operand " + operand + " out of bounds", OPERAND_OUT_OF_BOUNDS);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    //Clear the buffer (Cleared it this late in case we need it for displaying an error message.)
                    buffer.clear();
                    //Append the buffer onto the instruction
                    instruction.append(operand);
                    //Clear the buffer
                    operand.clear();
                    //Push the instruction onto instructions
                    instructions.push_back(instruction);
                    //Clear the instruction buffer
                    instruction.clear();
                }
                    //The other keywords work the same way as explained above
                else if (buffer == "ADD") {
                    //If an operand wasn't provided
                    if (!operand_exists(current)) {
                        printf("%s Missing operand at line: %d, col: %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    instruction.append("0x1");
                    buffer.clear();
                    advance();
                    while (current != '\n') {
                        col += 1;
                        //If an invalid character was provided
                        if (!char_is_hex(current)) {
                            printf("%s Invalid char %c at line: %d, col: %d\n", error, current, line, col);
                            buffer.clear();
                            this->instructions.clear();
                            this->text.clear();
                            return;
                        }
                        operand.push_back(current);
                        advance();
                    }
                    instruction.append(operand);
                    operand.clear();
                    instructions.push_back(instruction);
                    instruction.clear();
                }
                else if (buffer == "SUB") {
                    //If an operand wasn't provided
                    if (!operand_exists(current)) {
                        printf("%s Missing operand at line: %d, col: %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    instruction.append("0x2");
                    buffer.clear();
                    advance();
                    while (current != '\n') {
                        //If an invalid character was provided
                        if (!char_is_hex(current)) {
                            printf("%s Invalid char %c at line: %d, col: %d\n", error, current, line, col);
                            buffer.clear();
                            this->instructions.clear();
                            this->text.clear();
                            return;
                        }
                        col += 1;
                        operand.push_back(current);
                        advance();
                    }
                    instruction.append(operand);
                    operand.clear();
                    instructions.push_back(instruction);
                    instruction.clear();
                }
                else if (buffer == "LOAD") {
                    //If an operand wasn't provided
                    if (!operand_exists(current)) {
                        printf("%s Missing operand at line: %d, col: %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    instruction.append("0x3");
                    buffer.clear();
                    advance();
                    while (current != '\n') {
                        //If an invalid character was provided
                        if (!char_is_hex(current)) {
                            printf("%s Invalid char %c at line: %d, col: %d\n", error, current, line, col);
                            buffer.clear();
                            this->instructions.clear();
                            this->text.clear();
                            return;
                        }
                        col += 1;
                        operand.push_back(current);
                        advance();
                    }
                    instruction.append(operand);
                    operand.clear();
                    instructions.push_back(instruction);
                    instruction.clear();
                }
                else if (buffer == "SAVE") {
                    //If an operand wasn't provided
                    if (!operand_exists(current)) {
                        printf("%s Missing operand at line: %d, col: %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                    instruction.append("0x4");
                    buffer.clear();
                    advance();
                    while (current != '\n') {
                        //If an invalid character was provided
                        if (!char_is_hex(current)) {
                            printf("%s Invalid char %c at line: %d, col: %d\n", error, current, line, col);
                            buffer.clear();
                            this->instructions.clear();
                            this->text.clear();
                            return;
                        }
                        col += 1;
                        operand.push_back(current);
                        advance();
                    }
                    instruction.append(operand);
                    operand.clear();
                    instructions.push_back(instruction);
                    instruction.clear();
                }
                else if (buffer == "PRINT") {
                    if (!operand_exists(current)) {
                        instruction.append("0xf000");
                        buffer.clear();
                        instructions.push_back(instruction);
                        instruction.clear();
                    }
                    else {
                        printf("%s Unnecessary operand for print instruction at line %d, col %d\n", error, line, col);
                        buffer.clear();
                        this->instructions.clear();
                        this->text.clear();
                        return;
                    }
                }
                else {
                    printf("%s Invalid instruction at line %d, col %d\n", error, line, col);
                    buffer.clear();
                    this->instructions.clear();
                    this->text.clear();
                }
            }
        }
        advance();
    }
}

void Lexer::set_file_text(const std::string &new_text) {
    this->text = new_text;
}

char Lexer::peek(int steps) {
    if (this->current == '\0') return '\0';
    else return this->text[this->index + steps];
}

bool Lexer::char_is_hex(char c) {
    if ((c >= 'A' & c <= 'F') || (c >= 'a' && c <= 'f') || isdigit(c))
        return true;
    return false;
}

//TODO: CHECK HERE
bool Lexer::operand_exists(char c) {
    if (c == '\n') {
        return false;
    }
    char next = this->peek(1);
    if (isalnum(next)) return true;
    return false;
}

word Lexer::string_to_hex(std::string& str) {
    str = str.substr(2);
    std::stringstream hex_stream;
    hex_stream << std::hex << str;
    word result;
    hex_stream >> result;
    return result;
}

bool Lexer::operand_in_bounds(std::string& str) {
    std::stringstream hex_stream;
    hex_stream << std::hex << str;
    dword test_var;
    hex_stream >> test_var;
    if (test_var > 0xffff || test_var < 0) {
        return false;
    }
    return true;
}