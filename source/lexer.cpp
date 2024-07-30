#include "../headers/lexer.h"

Lexer::Lexer(const std::string &file_name) {
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

void Lexer::buffer_add() {
    this->buffer.push_back(this->current);
}

void Lexer::buffer_clear() {
    this->buffer.clear();
}

void Lexer::tokenize() {
    //Instruction buffer for pushing onto instructions vector.
    std::string instruction{};
    this->index = 0;
    this->current = this->text[this->index];
    printf("Text: %s\n", text.c_str());
    while (current != '\0') {
        while (isalnum(current)) {
            printf("Current: %d, %c\n", this->current, this->current);
            printf("Index: %ld\n", this->index);
            //Push char onto buffer
            buffer_add();
            //Advance further
            advance();
            //If INT instruction has been encountered
            if (buffer == "INT") {
                //Use the 0x5 prefix
                instruction.append("0x5");
                //Clear the buffer
                buffer_clear();
                //Advance further
                advance();
                //Until the newline character
                while (current != '\n') {
                    //TODO: Add checks here
                    //Push char onto buffer
                    buffer_add();
                    //Advance further
                    advance();
                }
                //Append the buffer onto the instruction
                instruction.append(buffer);
                //Clear the buffer
                buffer_clear();
                //Push the instruction onto instructions
                instructions.push_back(instruction);
                //Clear the instruction buffer
                instruction.clear();
            }
                //The other keywords work the same way as explained above
            else if (buffer == "ADD") {
                instruction.append("0x1");
                buffer_clear();
                advance();
                while (current != '\n') {
                    buffer_add();
                    advance();
                }
                instruction.append(buffer);
                buffer_clear();
                instructions.push_back(instruction);
                instruction.clear();
            }
            else if (buffer == "SUB") {
                instruction.append("0x2");
                buffer_clear();
                advance();
                while (current != '\n') {
                    buffer_add();
                    advance();
                }
                instruction.append(buffer);
                buffer_clear();
                instructions.push_back(instruction);
                instruction.clear();
            }
            else if (buffer == "LOAD") {
                instruction.append("0x3");
                buffer_clear();
                advance();
                while (current != '\n') {
                    buffer_add();
                    advance();
                }
                instruction.append(buffer);
                buffer_clear();
                instructions.push_back(instruction);
                instruction.clear();
            }
            else if (buffer == "SAVE") {
                instruction.append("0x4");
                buffer_clear();
                advance();
                while (current != '\n') {
                    buffer_add();
                    advance();
                }
                instruction.append(buffer);
                buffer_clear();
                instructions.push_back(instruction);
                instruction.clear();
            }
            else if (buffer == "PRINT") {
                instruction.append("0xf000");
                buffer_clear();
                instructions.push_back(instruction);
                instruction.clear();
            }
        }
        advance();
    }
}

void Lexer::set_file_text(const std::string &new_text) {
    this->text = new_text;
}

char Lexer::peek() {
    if (this->current == '\0') return '\0';
    else return this->text[this->index + 1];
}
