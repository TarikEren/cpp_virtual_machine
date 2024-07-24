#ifndef CPP_VIRTUAL_MACHINE_LOGGER_H
#define CPP_VIRTUAL_MACHINE_LOGGER_H

#include <string>
#include "errors.h"

typedef enum level{
    NONE,
    INFO,
    WARNING,
    ERROR,
    FATAL_ERROR
}level_t;

void logger(level_t level, const std::string& message, error_type error);

#endif
