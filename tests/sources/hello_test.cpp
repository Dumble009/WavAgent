#include <gtest/gtest.h>
#include "test_lib.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(LinkTest, BasicAssertions)
{
    EXPECT_EQ(1 + 2, testLib::add(1, 2));
}