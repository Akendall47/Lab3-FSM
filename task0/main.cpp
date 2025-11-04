// Include the GoogleTest framework header file
// This gives you access to testing tools like TEST_F, EXPECT_EQ, etc.
#include "gtest/gtest.h"

// A simple function that we want to test.
// It takes two integers and returns their sum.
int add(int a, int b) { 
    return a + b; 
}

// Define a "test fixture" class for GoogleTest.
// A test fixture is like a reusable test setup — if you have multiple tests
// that need the same preparation or cleanup, you can define them here.
class TestAdd : public ::testing::Test
{
protected:
    // The 'protected' keyword means only this class and its derived classes can access these methods.

    // The SetUp() function runs BEFORE each test in this test fixture.
    // You can use it to initialize variables, allocate memory, etc.
    void SetUp() override
    {
        // Runs before each test
    }

    // The TearDown() function runs AFTER each test in this test fixture.
    // Use it to clean up resources.
    void TearDown() override
    {
        // Runs after each test
    }
};

// The TEST_F macro defines a test that uses a fixture (the "_F" stands for "Fixture").
// The first argument is the fixture name (TestAdd).
// The second argument is the test name (AddTest).
TEST_F(TestAdd, AddTest)
{
    // EXPECT_EQ checks if two values are equal.
    // If add(2, 4) == 6, this test passes.
    EXPECT_EQ(add(2, 4), 6);
}

// Another test case using the same fixture (TestAdd).
// You can write as many TEST_F blocks as you want.
TEST_F(TestAdd, AddTest2)
{
    // This test intentionally fails to show what a failed test looks like.
    // EXPECT_EQ will fail because 2 + 2 = 4, not 5.
    EXPECT_EQ(add(2, 2), 5);
}

// The main() function for running all Google tests.
// GoogleTest provides a helper function that automatically discovers and runs every test.
int main(int argc, char **argv)
{
    // Initializes GoogleTest with command-line arguments (if any).
    testing::InitGoogleTest(&argc, argv);

    // Runs all tests that have been defined using TEST or TEST_F.
    // Returns 0 if all tests pass, or 1 if any test fails.
    auto res = RUN_ALL_TESTS();

    // Return the result code to the operating system.
    return res;
}
