#ifndef CPP_VIRTUAL_MACHINE_MACHINE_H
#define CPP_VIRTUAL_MACHINE_MACHINE_H

#include <iostream>
#include "errors.h"

#ifndef word
#define word uint16_t
#endif
#define STACK_SIZE 10 //For now

class Machine {
private:
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
    //Fetch operand from address
    word fetch(word address);
    //Add fetched operand to ac value
    word add(word operand);
    //Subtract fetched operand from ac value
    word sub(word operand);
    //Save ac value to provided address
    void save(word address);
    //Load fetched operand and set ac value as said value
    void load(word address);
    //Execute commands on the stack
    void execute();
    //Print the top of the stack
    //TODO: Might change this to an addressed instruction and print a fetched operand.
    void print();
};


#endif
