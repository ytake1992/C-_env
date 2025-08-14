#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "calculator.h"
#include "logger.h"

using ::testing::_;
using ::testing::StrEq;

class MockLogger : public Logger {
public:
    MOCK_METHOD1(log, void(const char*));
    MOCK_CONST_METHOD0(get_last_log, const char*());
};

class CalculatorMockTest : public ::testing::Test {
protected:
    MockLogger mock_logger;
    Calculator calc;

    CalculatorMockTest() : calc(&mock_logger) {}
    void SetUp() {}
    void TearDown() {}
};

TEST_F(CalculatorMockTest, AddLogsCorrectly) {
    EXPECT_CALL(mock_logger, log(StrEq("Add: 2 + 3 = 5")));
    calc.add(2, 3);
}

TEST_F(CalculatorMockTest, MultiplyLogsCorrectly) {
    EXPECT_CALL(mock_logger, log(StrEq("Multiply: 2 * 3 = 6")));
    calc.multiply(2, 3);
}