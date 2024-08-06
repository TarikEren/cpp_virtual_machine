#include "headers/compiler.h"
#include "headers/create.h"
#include <fstream>

//TODO: A general refactoring.
//      Change the logger function
//TODO: A way to view the stack would be nice.

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
                //Lexer obj
                Lexer lexer;
                //Read file and set text as said file's contents
                lexer.read_file(file_name);
                //Actual compiler function.
                Compiler::compile(lexer);
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
            for (const auto& arg : args) {
                printf("%s\n", arg.c_str());
            }
            if (args.size() == 1) {
                //If no file name was provided, log this.
                logger(FATAL_ERROR, "No file name provided", FILENAME_NOT_PROVIDED);
            }
            else {
                //File name
                std::string file_name = args[1];
                //If the provided file name doesn't have a .basm extension,
                //append one to the file name.
                if (!ext_check(file_name)) file_name += ".basm";
                std::fstream file_check(file_name, std::ios::in);
                if (!file_check.is_open()) {
                    create_basm(file_name);
                }
                else {
                    logger(ERROR, "File already exists", FILE_EXISTS);
                }
            }
        }
        else if (command == "exit") {
            //If the user types in "exit" continue
            continue;
        }
        else if (command == "help") {
            printf("A simple stack based virtual computer made in C++\n"
                   "It lets the user create and compile \".basm\" files.\n"
                   "Commands and usage:\n"
                   "ADD 'address':\tFetches operand from address and adds it to AX register's value\n"
                   "SUB 'address':\tFetches operand from address and subtracts it from AX register's value\n"
                   "SAVE 'address':\tSaves AX register's value to a location within the stack\n"
                   "LOAD 'address':\tFetches operand from address and sets AX register's value as the fetched operand\n"
                   "INT 'value':\tSets the AX register's value as the provided operand\n"
                   "PRINT:\t\t\tPrints the value on top of the stack\n");
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