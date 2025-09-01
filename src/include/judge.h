#ifndef JUDGE_H
#define JUDGE_H
#include "result.h"
class Judge {
public:
    virtual ~Judge() {}
    virtual bool evaluate(const Result& result) = 0;
};
#endif
