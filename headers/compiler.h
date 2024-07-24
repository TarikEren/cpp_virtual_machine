#ifndef CPP_VIRTUAL_MACHINE_COMPILER_H
#define CPP_VIRTUAL_MACHINE_COMPILER_H

#include "lexer.h"
#include "machine.h"

class Compiler {
public:
    Compiler() = default;
    void compile(const std::string& filename);
};

#endif