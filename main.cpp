#include "headers/machine.h"

/*
 * ADD XXX
 * SUB XXX
 * SAVE XXX
 * LOAD XXX
 * INT XXXX
 * */

int main() {
    Machine machine;
    machine.push(0x4009);
    machine.push(0x1008);
    machine.push(0x5002);
    machine.push(0x4008);
    machine.push(0x5001);
    machine.execute();
    machine.dump_stack();
}

