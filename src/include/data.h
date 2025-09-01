#ifndef DATA_H
#define DATA_H

#include <vector>
#include "result.h"

class Data {
    public:
        Data(const std::vector<Result>& results) : results_(results) {}
        const std::vector<Result>& getResults() const { return results_; }
        int getSize() const { return results_.size(); }
    private:
        std::vector<Result> results_;
};

#endif