#include "../headers/machine.h"

word Machine::push(word new_word) {
    //Buffer overflow
    if (this->stack_ptr == STACK_SIZE - 1) {
        logger(FATAL_ERROR, "Stack overflow", STACK_OVERFLOW);
        return -1;
    }
    this->stack_ptr += 1;
    this->stack[this->stack_ptr] = new_word;
    std::string message = "Pushed value " + hex_to_string(new_word) + " to position " + int_to_string(this->stack_ptr);
    logger(INFO, message, NONE);
    return this->stack[this->stack_ptr];
}

word Machine::pop() {
    //Buffer underflow
    if (this->stack_ptr == -1) {
        logger(FATAL_ERROR, "Stack underflow", STACK_UNDERFLOW);
        return -1;
    }
    this->stack_ptr -= 1;
    std::string message = "Popped value from position " + int_to_string(this->stack_ptr + 1);
    logger(INFO, message, NONE);
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
    bool end_process = false;
    while (this->stack_ptr != -1 && !end_process) {
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
            std::string message = "Invalid address " + hex_to_string(address);
            logger(FATAL_ERROR, message, INVALID_ADDRESS);
            break;
        }
        if (opcode == 0x1) {
            this->ax += this->stack[index];
            std::string message = "Added value " + hex_to_string(this->stack[index]) + " to AX";
            logger(INFO, message, NONE);
        }
        else if (opcode == 0x2) {
            this->ax -= this->stack[index];
            std::string message = "Subtracted value " + hex_to_string(this->stack[index]) + " from AX";
            logger(INFO, message, NONE);
        }
        else if (opcode == 0x3) {
            this->ax = this->stack[index];
            std::string message = "Loaded value " + hex_to_string(this->stack[index]) + " from address" + hex_to_string(address);
            logger(INFO, message, NONE);
        }
        else if (opcode == 0x4) {
            if (this->stack[index] != 0x0) {
                std::string message = "Target address " + hex_to_string(address) + " is full";
                logger(FATAL_ERROR, message, TARGET_ADDRESS_FULL);
                end_process = true;
            }
            this->stack[index] = this->ax;
            std::string message = "Saved value " + hex_to_string(this->ax) + " to address " + hex_to_string(address);
            logger(INFO, message, NONE);
        }
        else if (opcode == 0x5) {
            this->ax = operand;
            std::string message = "Set AX as " + hex_to_string(operand);
            logger(INFO, message, NONE);
        }
        else if (opcode == 0xf) {
            printf("\x1b[32mOUTPUT:\x1b[0m Top of the stack: %x\n", this->stack[STACK_SIZE-1]);
        }
        if (!end_process) this->pop();
    }
}

std::string Machine::hex_to_string(word hex) {
    std::string result;
    std::stringstream ss;
    ss << std::hex << hex;
    result = ss.str();
    return result;
}

std::string Machine::int_to_string(int val) {
    std::string result;
    std::stringstream ss;
    ss << val;
    result = ss.str();
    return result;
}
