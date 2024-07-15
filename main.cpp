#include <iostream>

//TODO: Refactor
//TODO: Add locations for which line caused an error if an error has been encountered.

#define word uint16_t
#define STACK_SIZE 5        //For now

typedef enum error_code {
    STACK_OVERFLOW,
    STACK_UNDERFLOW
}error_code;

class Memory {
private:
    word stack[STACK_SIZE]{};   //Call stack
    word ax = 0;                //AC register
    size_t sp = -1;             //Stack pointer
public:
    word push(word);
    word pop();
    void dump_stack();
};

word Memory::push(word new_word) {
    if (this->sp == STACK_SIZE) {
        printf("FATAL ERROR: Stack overflow\n");    //TODO: Print which word caused the overflow.
        exit(STACK_OVERFLOW);
    }
    this->sp += 1;                      //Increase the stack pointer
    this->stack[this->sp] = new_word;   //Set the current stack slot as the new word
    printf("INFO: Pushed value: %x\n", this->stack[this->sp]);
    return this->stack[this->sp];       //Return the pushed value
}

word Memory::pop() {
    if (this->sp == -1) {
        printf("FATAL ERROR: Stack underflow\n");   //TODO: Print which word caused the underflow.
        exit(STACK_UNDERFLOW);
    }
    this->sp -= 1;                      //Decrease the stack pointer
    printf("INFO: Popped value: %x\n", this->stack[this->sp + 1]);
    return this->stack[this->sp + 1];   //Return the popped value
}

void Memory::dump_stack() {
    printf("STACK START\n");
    for (int i = STACK_SIZE-1; i >= 0; i--) {
        printf("%d:\t%x\n", i, this->stack[i]);
    }
    printf("STACK END\n");
}

int main() {
    Memory memory_obj{};
    memory_obj.push(0xffff);
    memory_obj.pop();
    memory_obj.dump_stack();
}
