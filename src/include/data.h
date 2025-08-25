#include <vector>
class Data {
public:
    Data(const std::vector<Result>& results) : results_(results) {}
    const std::vector<Result>& getResults() const { return results_; }
    int getSize() const { return results_.size(); }
private:
    std::vector<Result> results_;
};