#include "../headers/machine.h"

word Machine::push(word new_word) {
    //Buffer overflow
    if (this->stack_ptr == STACK_SIZE - 1) {
        printf("ERROR: Stack is full. Cannot push to stack\n");
        return -1;
    }
    this->stack_ptr += 1;
    this->stack[this->stack_ptr] = new_word;
    printf("INFO: Pushed value %x to position %d\n", new_word, this->stack_ptr);
    return this->stack[this->stack_ptr];
}

word Machine::pop() {
    //Buffer underflow
    if (this->stack_ptr == -1) {
        printf("ERROR: Stack is empty. Cannot pop from stack\n");
        return -1;
    }
    this->stack_ptr -= 1;
    printf("INFO: Popped value from position %d\n", this->stack_ptr + 1);
    return this->stack[this->stack_ptr];
}

int Machine::get_index(word address) {
    //This rather dumb solution which only works for a fixed addressed memory so change how this function works
    //if you are going to change how the memory works
    int index = (address / 0x100) * 256 + ((address / 0x10) % 0x10) * 16 + address % 0x10;
    return index;
}

void Machine::dump_stack() {
    printf("STACK START\n");
    for (int i = STACK_SIZE-1; i >= 0; i--) {
        printf("%d = %x\n", i, this->stack[i]);
    }
    printf("STACK END\n");
}

void Machine::execute() {
    //Execute the instruction on top of the stack.
    word address{}, operand{}, instruction{}, opcode{}, index{};
    while (this->stack_ptr != -1) {
        instruction = this->stack[stack_ptr];
        opcode = instruction / 0x1000;
        if (opcode == 0x5) { //Operand including instruction
            operand = instruction % 0x1000;
            address = 0x0;
        }
        else if (opcode == 0xf) { //No operand / address
            address = 0x0;
            operand = 0x0;
        }
        else { //Addressed instruction
            address = instruction % 0x1000;
            operand = 0x0;
        }
        index = get_index(address);
        if (index < 0 || index >= STACK_SIZE) {
            printf("Invalid address %x. Ending process with exit code %d\n", address, INVALID_ADDRESS);
            break;
        }
        if (opcode == 0x1) {
            this->ax += this->stack[index];
        }
        else if (opcode == 0x2) {
            this->ax -= this->stack[index];
        }
        else if (opcode == 0x3) {
            this->ax = this->stack[index];
        }
        else if (opcode == 0x4) {
            this->stack[index] = this->ax;
        }
        else if (opcode == 0x5) {
            this->ax = address;
        }
        else if (opcode == 0xf) {
            printf("Top of the stack: %x\n", this->stack[STACK_SIZE-1]);
        }
        this->pop();
    }
}

void Machine::print() {
    printf("OUTPUT: Top of the stack: %hu\n", this->stack[STACK_SIZE-1]);
}
