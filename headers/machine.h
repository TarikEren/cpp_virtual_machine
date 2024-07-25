#ifndef CPP_VIRTUAL_MACHINE_MACHINE_H
#define CPP_VIRTUAL_MACHINE_MACHINE_H

#include <iostream>
#include <sstream>
#include "errors.h"
#include "logger.h"

#ifndef word
#define word uint16_t
#endif

class Machine {
private:
    //Stack size
    static constexpr size_t STACK_SIZE = 10; //In case of an error, try using a define macro to define this variable.
    //The actual stack
    word stack[STACK_SIZE]{0};
    //AX register. Used for mathematical operations.
    word ax = 0x0;
    //Stack pointer.
    int stack_ptr = -1;
public:
    //Push the provided word onto the stack
    word push(word);

    //Pop from the stack
    word pop();

    //Print the stack
    void dump_stack();

    //Turns address value into an index value
    int get_index(word);

    //Execute commands on the stack
    void execute();

    //Turns hex values into strings
    std::string hex_to_string(word hex);

    //Turns int values into strings
    std::string int_to_string(int val);
};


#endif
