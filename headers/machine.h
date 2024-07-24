#ifndef CPP_VIRTUAL_MACHINE_MACHINE_H
#define CPP_VIRTUAL_MACHINE_MACHINE_H

#include <iostream>
#include "errors.h"
#include "logger.h"

#ifndef word
#define word uint16_t
#endif

class Machine {
private:
    static constexpr size_t STACK_SIZE = 10; //In case of an error, try using a define macro to define this variable.
    word stack[STACK_SIZE]{0};
    word ax = 0x0;
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

    //Print the top of the stack
    //TODO: Might change this to an addressed instruction and print a fetched operand.
    void print();
};


#endif
