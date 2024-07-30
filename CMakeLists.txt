cmake_minimum_required(VERSION 3.22)
project(cpp_virtual_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_virtual_machine main.cpp
        headers/machine.h
        source/machine.cpp
        headers/lexer.h
        headers/lexer.h
        source/lexer.cpp
        headers/errors.h
        headers/compiler.h
        source/compiler.cpp
        headers/logger.h
        source/logger.cpp
        headers/create.h
)
