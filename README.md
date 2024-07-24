# cpp_virtual_machine

A RISC architecture machine simulation made in c++ (Still work in progress, functionality might change drastically.)
For now only it only works as a compiler. New functionalities might be added in the future.

### Usage

./cpp_virtual_machine filename.basm


### Functions

| Function name | Hex value | Description                                                                           |
|---------------|-----------|---------------------------------------------------------------------------------------|
| ADD           | 0x1XXX    | Adds a value to the AX register                                                       |
| SUB           | 0x2XXX    | Subtracts a value from the AX register                                                |
| LOAD          | 0x3XXX    | Loads a value from the stack                                                          |
| SAVE          | 0x4XXX    | Saves a value to the stack                                                            |
| INT           | 0x5XXX    | Sets the AX register's value as an integer                                            |
| PRINT         | 0xF000    | Prints the top of the stack (Might change this to an addressed instruction later on.) |
