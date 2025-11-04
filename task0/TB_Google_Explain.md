googleTest c++

5. Expectations
EXPECT_EQ(add(2, 4), 6);

    This checks if:
    add(2, 4) == 6

Other examples:

    EXPECT_TRUE(condition)
    EXPECT_FALSE(condition)

    EXPECT_NE(val1, val2) // not equal
    EXPECT_LT(a, b) // less than


Summary
Part	    Purpose
#include "gtest/gtest.h"	               Use GoogleTest features
int add(...)	                           Function being tested
class TestAdd : public ::testing::Test	   Setup/teardown for tests
TEST_F(TestAdd, Name)	                    Defines a test using that fixture
EXPECT_EQ(...)	                            Checks results
main()	                                    Runs all tests