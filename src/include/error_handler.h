#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdexcept>

class ErrorHandler {
public:
    ErrorHandler();
    int divide(int a, int b); // 例外を投げる
    int divide_safe(int a, int b, bool* error); // 既存のエラーフラグ版
};

#endif