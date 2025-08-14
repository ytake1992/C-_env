#include "error_handler.h"

ErrorHandler::ErrorHandler() {}

int ErrorHandler::divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

int ErrorHandler::divide_safe(int a, int b, bool* error) {
    *error = (b == 0);
    if (*error) {
        return 0;
    }
    return a / b;
}