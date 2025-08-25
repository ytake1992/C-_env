#include <gtest/gtest.h>
#include "decision_maker.h"
#include "database_searcher.h"
class StubDatabaseSearcher : public DatabaseSearcher {
public:
    Data* search(const std::string& query) {
        if (query == "valid") return new Data(42);
        return nullptr;
    }
};
TEST(DecisionMakerTest, MakeDecision) {
    StubDatabaseSearcher stub_searcher;
    DecisionMaker decision_maker(&stub_searcher);
    EXPECT_TRUE(decision_maker.makeDecision("valid"));
    EXPECT_FALSE(decision_maker.makeDecision("invalid"));
}