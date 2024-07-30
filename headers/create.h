#ifndef CPP_VIRTUAL_MACHINE_CREATE_H
#define CPP_VIRTUAL_MACHINE_CREATE_H

#include "compiler.h"
#include <fstream>

void create_basm(const std::string& new_filename) {
//File object.
    std::fstream file;

    //Create a file with that name.
    file.open(new_filename, std::ios::out);
    //TODO: Add checks for existing files.
    if (!file.is_open()) {
        //If the file could not be opened, log this.
        logger(FATAL_ERROR, "File could not open", COULD_NOT_OPEN_FILE);
    }
    else {
        //Buffer is for storing each line and contents is for storing
        //the entire file.
        std::string buffer{}, contents{};
        while (buffer != "END") {
            //Until the user sends a buffer containing the word "END"
            //Carriage return and print line starter.
            printf("\r>>> ");
            //Get a line from the user and save it into the buffer.
            std::getline(std::cin, buffer);
            if (!buffer.empty() && buffer != "END") {
                //If the buffer is not empty nor is it "END"
                //push a newline onto the buffer.
                buffer.push_back('\n');
                //Append the buffer to the contents variable
                contents.append(buffer);
                //Clear the buffer.
                buffer.clear();
            }
        }
        //Lexer object
        Lexer lexer;
        //Set the text variable as the contents variable.
        //text variable is the main string that the tokenizer
        //operates on.
        lexer.set_file_text(contents);
        //Compiler object
        Compiler compiler;
        //Compile using the provided lexer object.
        compiler.compile(lexer);
        //Write the contents on to the open file.
        file << contents;
        //Close said file.
        file.close();
    }
}


#endif
