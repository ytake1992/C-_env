#include "decision_maker.h"

bool DecisionMaker::makeDecision(const std::string& query) {
    std::vector<Result>* results = searcher_->search(query);
    if (!results) return false;
    bool result = false;
    for (int i = 0; i < results->size(); ++i) {
        if (judge_->evaluate((*results)[i])) {
            result = true;
            break;
        }
    }
    delete results; // 動的割り当ての場合
    return result;
}