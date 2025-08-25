#include <vector>
#include "result.h"

class DatabaseSearcher {
public:
    virtual std::vector<Result>* search(const std::string& query);
};