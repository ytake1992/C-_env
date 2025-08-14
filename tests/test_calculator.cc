#include <gtest/gtest.h>
#include "calculator.h"
#include "logger.h"

class CalculatorTest : public ::testing::Test {
protected:
    Logger logger;
    Calculator calc;

    CalculatorTest() : calc(&logger) {}

    void SetUp() {}
    void TearDown() {}
};

TEST_F(CalculatorTest, AddTest) {
    EXPECT_EQ(5, calc.add(2, 3));
    EXPECT_EQ(0, calc.add(0, 0));
}

TEST_F(CalculatorTest, MultiplyTest) {
    EXPECT_EQ(6, calc.multiply(2, 3));
    EXPECT_EQ(0, calc.multiply(0, 5));
}

TEST_F(CalculatorTest, LastResultTest) {
    calc.add(2, 3); // last_result = 5
    EXPECT_EQ(5, calc.get_last_result());
    calc.multiply(4, 2); // last_result = 8
    EXPECT_EQ(8, calc.get_last_result());
}