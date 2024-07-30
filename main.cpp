#include "headers/compiler.h"
#include "headers/create.h"
#include <fstream>

//TODO: A general refactoring.
//      Group functions in include files
//TODO: Might remove lexer.h and use those functions in compiler.h
//TODO: Add a makefile for building on release.
//TODO: Add error checking in the lexer
//      Check for value out of bounds in lexer
//TODO: Add error checking in the shell
//      Check for valid opcode-operand pairs (i.e. print command doesn't take any operands)
//TODO: Display error codes as error values (i.e. INVALID_COMMAND)
//TODO: After exiting the shell, program prints out another > for some reason. Fix it.

void clear_screen() {
    printf("\033[2J\033[H");
}

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

bool ext_check(const std::string& filename) {
    //TODO: Yeah. Refactor this, thing.
    size_t size = filename.size();
    if (    filename[size-5] != '.' ||
            filename[size-4] != 'b' ||
            filename[size-3] != 'a' ||
            filename[size-2] != 's' ||
            filename[size-1] != 'm')
        return false;
    return true;
}

int main() {

    //Input and command buffers.
    //Input refers to the primary user input. It can be a command with arguments.
    //Command refers to the actual executable command.
    std::string input{}, command{};
    //Vector for holding arguments. This includes command itself.
    std::vector<std::string> args{};
    //Version. Because why not?
    std::string version = "0.0.1";

    while (input != "exit") {
        //Return to the beginning and print the line starter.
        printf("\r> ");
        //Get user input.
        //TODO: Check for empty input.
        std::getline(std::cin, input);
        //Parse said user input.
        args = parse_arguments(input);
        //By definition, the first arg has to be the command itself.
        command = args[0];

        //Check for commands.
        if (command == "compile") {
            //Compile .basm files
            if (args.size() == 1) {
                //If no file has been provided log this
                logger(ERROR, "No file provided", FILE_NOT_PROVIDED);
            }
            else {
                //The second arg has to be the file name.
                std::string file_name = args[1];
                //Compiler object.
                Compiler compiler;
                //Actual compiler function.
                compiler.compile(file_name);
            }
        }
        else if (command == "clear"){
            //Clear the screen.
            clear_screen();
        }
        else if (command == "version") {
            //Log the function because it looks prettier.
            logger(INFO, version, NONE);
        }
        else if (command == "create") {
            //Create .basm file
            //Note: Does not work as a proper text editor.
            //It simply takes lines from the user, appends them and pushes them
            //into a buffer which gets taken by the lexer and gets tokenized.
            //Then the machine executes the corresponding functions.
            if (args.size() == 1) {
                //If no file name was provided, log this.
                logger(FATAL_ERROR, "No file name provided", FILENAME_NOT_PROVIDED);
            }
            //File name
            std::string filename = args[1];
            //If the provided file name doesn't have a .basm extension,
            //append one to the file name.
            if (!ext_check(filename)) filename += ".basm";
            create_basm(filename);
        }
        else if (command == "exit") {
            //If the user types in "exit" continue
            continue;
        }
        //For some reason after the shell exits, the main cli program
        //takes in null terminator as input
        else if (command[0] != '\0'){
            std::string message = "Invalid input " + input;
            logger(ERROR, message, INVALID_COMMAND);
        }
    }
    //Upon successful termination, log this.
    logger(INFO, "Ending process with exit code 0", SUCCESS);
    return 0;
}