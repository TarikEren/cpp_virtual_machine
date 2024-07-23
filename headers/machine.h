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
    word push(word);
    word pop();
    void dump_stack();
    word fetch(word address);
    word add(word operand);
    word sub(word operand);
    void save(word address);
    void load(word address);
    void execute();
};


#endif
