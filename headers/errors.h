#ifndef CPP_VIRTUAL_MACHINE_ERRORS_H
#define CPP_VIRTUAL_MACHINE_ERRORS_H

//Error type enum for keeping track of return codes.
typedef enum error_type {
    SUCCESS = 0,
    TARGET_ADDRESS_FULL = 1,
    FILE_NOT_PROVIDED,
    FILE_NOT_FOUND,
    INVALID_COMMAND,
    FILENAME_NOT_PROVIDED,
    FILE_EXISTS,
    COULD_NOT_OPEN_FILE,
    INVALID_ADDRESS = 100,
    OPERAND_OUT_OF_BOUNDS,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    NONE = 0xfffff
}error_type;

#endif
