# cpp_virtual_machine

A cli program made in c++ that takes in commands and manipulates a basic computer simulation made in c++ (Still work in progress, functionality might change drastically.)

(Will add a build system in the future.)

### Usage

Simply build and run cpp_virtual_machine.
It's recommended to run the program from the terminal directly as it's a CLI program.

### Shell commands

compile: Compiles a .basm file and executes machine functions.
  Usage: compile filename.basm

### Assembler language

| Function name | Hex value | Description                                                                           |
|---------------|-----------|---------------------------------------------------------------------------------------|
| ADD           | 0x1XXX    | Adds a value to the AX register                                                       |
| SUB           | 0x2XXX    | Subtracts a value from the AX register                                                |
| LOAD          | 0x3XXX    | Loads a value from the stack                                                          |
| SAVE          | 0x4XXX    | Saves a value to the stack                                                            |
| INT           | 0x5XXX    | Sets the AX register's value                                                          |
| PRINT         | 0xF000    | Prints the top of the stack (Might change this to an addressed instruction later on.) |

### Todos

Add more commands for the shell.
Change the machine logic so that it doesn't kill the entire program.
Add a makefile.
/T
