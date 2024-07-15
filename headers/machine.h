#ifndef CPP_VIRTUAL_MACHINE_MACHINE_H
#define CPP_VIRTUAL_MACHINE_MACHINE_H

#include <iostream>

#define word uint16_t
#define STACK_SIZE 10 //For now

typedef enum error_type {
    INVALID_ADDRESS = 1, //Because the stack doesn't store any negative values for now,
    //using negative values for the error codes is valid.
    //Might use chars or strings in the future.
    INVALID_INSTRUCTION,
    TARGET_ADDRESS_FULL
}error_type;

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
