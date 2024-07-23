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

int get_index(word address) {
    //This rather dumb solution only works for a fixed addressed memory so change how this function works
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

bool address_check(word address) {
    //Check if the address within bounds of the stack.
    if (address >= 0 && address <= STACK_SIZE - 1)
        return true;
    printf("ERROR: Invalid address %x, ending program\n", address);
    exit(INVALID_ADDRESS);
}

word Machine::fetch(word address) {
    return this->stack[get_index(address)];
}

word Machine::add(word operand) {
    //TODO: Add checks for overflows and add an overflow flag with a carry register.
    //Add to the eax register value.
    this->ax += operand;
    return this->ax;
}

word Machine::sub(word operand) {
    //TODO: Add checks for underflows.
    //Subtract from the eax register value.
    this->ax -= operand;
    return this->ax;
}

void Machine::save(word address) {
    //If it passes the address checks, check if the address is full.
    if (this->stack[get_index(address)] != 0) {
        //If so, throw error.
        printf("Target address %x is full\n", address);
        exit(TARGET_ADDRESS_FULL);
    }
    //If not, save the value to the target.
    this->stack[get_index(address)] = this->ax;
}

void Machine::load(word address) {
    //Fetch operand and set eax value to the fetched operand.
    int value = fetch(address);
    this->ax = value;
}

void Machine::execute() {
    //Execute the instruction on top of the stack.
    while (this->stack_ptr != -1) {
        word instruction = this->stack[this->stack_ptr];
        word opcode = instruction / 0x1000;
        word address = instruction % 0x1000;
        //Address check
        address_check(address);
        word value;
        switch (opcode) {
            case 0x1:
                value = fetch(address);
                add(value);
                break;
            case 0x2:
                value = fetch(address);
                sub(value);
                break;
            case 0x3:
                load(address);
                break;
            case 0x4:
                save(address);
                break;
            case 0x5:
                this->ax = address;
                break;
            case 0xf:
                print();
                break;
            default:
                printf("Invalid instruction: %x\n", instruction);
                exit(INVALID_INSTRUCTION);

        }
        this->pop();
    }
}

void Machine::print() {
    printf("OUTPUT: Top of the stack: %hu\n", this->stack[STACK_SIZE-1]);
}
