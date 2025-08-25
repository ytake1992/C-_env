#include <gmock/gmock.h>
#include <vector>
#include "decision_maker.h"
#include "database_searcher.h"
#include "data.h"

class MockDatabaseSearcher : public DatabaseSearcher {
public:
    MOCK_METHOD1(search, std::vector<Result>*(const std::string&));
};

class MockJudge : public Judge {
public:
    MOCK_METHOD1(evaluate, bool(const Result&));
};

TEST(DecisionMakerMockTest, MakeDecisionWithValidData) {
    MockDatabaseSearcher mock_searcher;
    MockJudge mock_judge;
    std::vector<Result> test_results = {{1, "item1"}, {2, "item2"}};
    std::vector<Result>* results_ptr = new std::vector<Result>(test_results);
    EXPECT_CALL(mock_searcher, search("valid"))
        .WillOnce(::testing::Return(results_ptr));
    EXPECT_CALL(mock_judge, evaluate(::testing::Field(&Result::id, 1)))
        .WillOnce(::testing::Return(true));
    DecisionMaker decision_maker(&mock_searcher);
    decision_maker.setJudge(&mock_judge);
    EXPECT_TRUE(decision_maker.makeDecision("valid"));
}