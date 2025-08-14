#ifndef CALCULATOR_H
#define CALCULATOR_H

class Logger; // 前方宣言

class Calculator {
public:
    Calculator(Logger* logger); // 既存のコンストラクタ
    int add(int a, int b);
    int multiply(int a, int b);
    int get_last_result() const; // メンバー変数テスト用
private:
    int last_result;
    Logger* logger;
};

#endif