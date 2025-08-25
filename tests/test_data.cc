#include <gtest/gtest.h>
#include <vector>
#include "data.h"
TEST(DataTest, GetResultsAndSize) {
    std::vector<Result> test_results = {{1, "item1"}, {2, "item2"}};
    Data data(test_results);
    EXPECT_EQ(data.getSize(), 2);
    EXPECT_EQ(data.getResults()[0].id, 1);
    EXPECT_EQ(data.getResults()[0].value, "item1");
}