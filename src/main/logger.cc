#include "logger.h"
#include <string.h>

void Logger::log(const char* message) {
    strncpy(last_log, message, sizeof(last_log) - 1);
    last_log[sizeof(last_log) - 1] = '\0';
}

const char* Logger::get_last_log() const {
    return last_log;
}