#include "../headers/logger.h"

void logger(level_t level, const std::string& message, error_type error) {
    if (level == INFO) {
        printf("\x1b[36mINFO:\x1b[0m %s\n", message.c_str());
    }
    else if (level == WARNING) {
        printf("\x1b[33mWARNING:\x1b[0m %s\n", message.c_str());
    }
    else if (level == FATAL_ERROR) {
        printf("\x1b[31mERROR:\x1b[0m %s\n\x1b[36mINFO:\x1b[0m Exiting with error code %d\n", message.c_str(), error);
    }
    else if (level == ERROR) {
        printf("\x1b[31mERROR:\x1b[0m %s (Code %d)\n", message.c_str(), error);
    }
}