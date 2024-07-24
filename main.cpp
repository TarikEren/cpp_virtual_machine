#include "headers/compiler.h"

//TODO: Add a makefile for building on release.
//TODO: Change the machine logic so that it doesn't kill the entire program when it encounters a problem.
//TODO: Add error checking
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
            if (args[1].empty()) {
                printf("ERROR: No file provided\n");
                exit(NO_TARGET_FILE_PROVIDED);
            }
            std::string filename = args[1];
            Compiler compiler;
            compiler.compile(filename);
        }
        else if (command == "exit") {
            continue;
        }
        else {
            printf("ERROR: Invalid command %s\n", command.c_str());
        }
    }
    printf("Ending process with exit code %d\n", EXIT_SUCCESS);
}