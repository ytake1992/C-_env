#include <gtest/gtest.h>
#include "calculator.h"
#include "logger.h"

class DependencyTest : public ::testing::Test {
protected:
	Logger logger;
	Calculator calc;

	DependencyTest() : calc(&logger) {}
	void SetUp() {}
	void TearDown() {}
};

TEST_F(DependencyTest, CalculatorLogsAdd) {
	calc.add(2, 3);
	EXPECT_STREQ("Add: 2 + 3 = 5", logger.get_last_log());
}

TEST_F(DependencyTest, CalculatorLogsMultiply) {
	calc.multiply(2, 3);
	EXPECT_STREQ("Multiply: 2 * 3 = 6", logger.get_last_log());
}