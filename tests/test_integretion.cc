#include <gtest/gtest.h>
#include "decision_maker.h"
#include "database_searcher.h"
TEST(IntegrationTest, FullWorkflow) {
    DatabaseSearcher searcher;
    DecisionMaker decision_maker(&searcher);
    EXPECT_TRUE(decision_maker.makeDecision("valid"));
}