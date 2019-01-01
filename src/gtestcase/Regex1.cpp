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

TEST_F(REGEX, Basic)
{
    Regex a("abc");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(false, a.match("ab"));
    EXPECT_EQ(true, a.match("abc"));
    EXPECT_EQ(false, a.match("abca"));
}

TEST_F(REGEX, Percent1)
{
    Regex a("a%");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("aaa"));
    EXPECT_EQ(true, a.match("aa"));
    EXPECT_EQ(false, a.match("a"));
    EXPECT_EQ(false, a.match("baa"));
}

TEST_F(REGEX, Percent2)
{
    Regex a("%%%");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("aaa"));
    EXPECT_EQ(true, a.match("aadfasfaa"));
    EXPECT_EQ(false, a.match("aa"));
    EXPECT_EQ(false, a.match("a"));
    EXPECT_EQ(true, a.match("baa"));
}

TEST_F(REGEX, Underline)
{
    Regex a("a_c");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("a5c"));
    EXPECT_EQ(true, a.match("abc"));
    EXPECT_EQ(false, a.match("ab"));
    EXPECT_EQ(false, a.match("abd"));
    EXPECT_EQ(false, a.match("aca"));
}

TEST_F(REGEX, Wildcard1)
{
    Regex a("a_c%");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("a5caaaaaaasdfa238hr9g"));
    EXPECT_EQ(true, a.match("abc9283hfzbv"));
    EXPECT_EQ(false, a.match("ab"));
    EXPECT_EQ(false, a.match("abd"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, Wildcard2)
{
    Regex a("%a_c%");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("1a5caaaaaaasdfa238hr9g"));
    EXPECT_EQ(true, a.match("asdfafabc9283hfzbv"));
    EXPECT_EQ(false, a.match("asdfab"));
    EXPECT_EQ(false, a.match("abc"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, Set)
{
    Regex a("a[abc]c");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("aac"));
    EXPECT_EQ(true, a.match("abc"));
    EXPECT_EQ(true, a.match("acc"));
    EXPECT_EQ(false, a.match("adc"));
    EXPECT_EQ(false, a.match("ac"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, ExcludingSet)
{
    Regex a("a[^abc]c");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(false, a.match("aac"));
    EXPECT_EQ(false, a.match("abc"));
    EXPECT_EQ(false, a.match("acc"));
    EXPECT_EQ(true, a.match("adc"));
    EXPECT_EQ(false, a.match("ac"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, SetMixture)
{
    Regex a("[^abc][abc][^abc]");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("dad"));
    EXPECT_EQ(true, a.match("ebe"));
    EXPECT_EQ(true, a.match("fcf"));
    EXPECT_EQ(false, a.match("fdf"));
    EXPECT_EQ(false, a.match("adc"));
    EXPECT_EQ(false, a.match("ac"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, Mixture)
{
    Regex a("%[^abc]k[abc][^abc]");
    ASSERT_EQ(false, a.isDead());
    EXPECT_EQ(true, a.match("asdafdkad"));
    EXPECT_EQ(false, a.match("ebe"));
    EXPECT_EQ(false, a.match("fcf"));
    EXPECT_EQ(false, a.match("fdf"));
    EXPECT_EQ(false, a.match("adc"));
    EXPECT_EQ(false, a.match("ac"));
    EXPECT_EQ(false, a.match("aca"));
    EXPECT_EQ(false, a.match("1aca"));
}

TEST_F(REGEX, IllegalPattern)
{
    Regex a("[^[abc][^abc]");
    EXPECT_EQ(true, a.isDead());
    Regex b("]");
    EXPECT_EQ(true, b.isDead());
    Regex c("%%%%");
    EXPECT_EQ(false, c.isDead());
    Regex d("%%[%%");
    EXPECT_EQ(true, d.isDead());
}
