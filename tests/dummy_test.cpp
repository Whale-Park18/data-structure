#include <gtest/gtest.h>

#include <object.hpp>

TEST(DummyTest, SampleAssertion)
{
    EXPECT_EQ(1, 1);
}

TEST(DummyTest, AnotherAssertion)
{
    object obj;
    obj.do_something();

    EXPECT_TRUE(true);
}