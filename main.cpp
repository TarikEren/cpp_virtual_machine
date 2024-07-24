#include "headers/compiler.h"
#include "headers/logger.h"

//TODO: Add a makefile for building on release.
//TODO: Add error checking in the lexer
//      Check for value out of bounds in lexer

std::vector<std::string> parse_arguments(const std::string& arguments) {
    std::vector<std::string> argument_vector{};
    int i = 0;
    char current = arguments[i];
    std::string buffer{};
    while (current != '\0') {
        buffer.push_back(current);
        if (arguments[i+1] == ' ') {
            i++;
            current = arguments[i];
            argument_vector.push_back(buffer);
            buffer.clear();
        }
        i++;
        current = arguments[i];
    }
    argument_vector.push_back(buffer);
    buffer.clear();
    return argument_vector;
}

int main(int argc, char* argv[]) {
    std::string command;
    std::vector<std::string> args;
    while (command != "exit") {
        printf("> ");
        std::getline(std::cin, command);
        args = parse_arguments(command);
        if (args[0] == "compile") {
            if (args.size() == 1) {
                logger(ERROR, "No file provided", FILE_NOT_PROVIDED);
            }
            else {
                std::string file_name = args[1];
                Compiler compiler;
                compiler.compile(file_name);
            }
        }
        else if (command == "shell") {

        }
        else if (command == "exit") {
            continue;
        }
        else {
            printf("ERROR: Invalid command %s\n", command.c_str());
        }
    }
    logger(INFO, "Ending process with exit code 0", SUCCESS);
}