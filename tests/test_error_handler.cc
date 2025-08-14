#include <gtest/gtest.h>
#include "error_handler.h"

class ErrorHandlerTest : public ::testing::Test {
protected:
    ErrorHandler handler;
    bool error;

    void SetUp() { error = false; }
    void TearDown() {}
};

TEST_F(ErrorHandlerTest, DivideNormal) {
    EXPECT_EQ(2, handler.divide_safe(4, 2, &error));
    EXPECT_FALSE(error);
}

TEST_F(ErrorHandlerTest, DivideByZero) {
    EXPECT_EQ(0, handler.divide_safe(4, 0, &error));
    EXPECT_TRUE(error);
}

TEST_F(ErrorHandlerTest, DivideThrowsException) {
    EXPECT_THROW(handler.divide(4, 0), std::runtime_error);
    EXPECT_NO_THROW(handler.divide(4, 2));
}