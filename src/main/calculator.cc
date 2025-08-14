#include "calculator.h"
#include "logger.h"
#include <stdio.h>

Calculator::Calculator(Logger* logger) : last_result(0), logger(logger) {}

/**
 * @brief 加算関数 
 * @details あたえられた引数を加算した値を返す

*/
int Calculator::add(int a, int b) {
    last_result = a + b;
    char buf[256];
    snprintf(buf, sizeof(buf), "Add: %d + %d = %d", a, b, last_result);
    logger->log(buf);
    return last_result;
}

int Calculator::multiply(int a, int b) {
    last_result = a * b;
    char buf[256];
    snprintf(buf, sizeof(buf), "Multiply: %d * %d = %d", a, b, last_result);
    logger->log(buf);
    return last_result;
}

int Calculator::get_last_result() const {
    return last_result;
}