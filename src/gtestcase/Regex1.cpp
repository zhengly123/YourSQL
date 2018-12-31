//
// Created by eric on 18-12-31.
//

#include <algorithm>
#include <gtest/gtest.h>
#include "../Regex/Regex.h"
class REGEX : public :: testing :: Test
{
protected:
    void SetUp () override
    {
    }
    void TearDown () override
    {
    }
};

TEST_F(REGEX, SELECT_SingleTable)
{
    Regex a("a%");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("aaa"));
    EXPECT_EQ(true, a.match("a"));
    EXPECT_EQ(true, a.match("baa"));
}

TEST_F(REGEX, SELECT_DoubleTable)
{
}
