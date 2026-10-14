#include <gtest/gtest.h>

#include <set>
#include <string_view>

#include <taskscheduler/Error.h>
#include <taskscheduler/ErrorFunctions.h>

using namespace taskscheduler;

// Proves: each code has the expected printable name.
TEST(ErrorTest, ToStringGivesExpectedNames)
{
    EXPECT_EQ(ToString(ErrorCode::EmptyCallable), "EmptyCallable");
    EXPECT_EQ(ToString(ErrorCode::JobThrewException), "JobThrewException");
    EXPECT_EQ(ToString(ErrorCode::JobThrewUnknown), "JobThrewUnknown");
}

// Proves: every code has a non-empty name, and no two codes share one.
TEST(ErrorTest, ToStringNamesAreDistinct)
{
    std::set<std::string_view> names;
    for (ErrorCode code : {ErrorCode::EmptyCallable, ErrorCode::JobThrewException,
                           ErrorCode::JobThrewUnknown})
    {
        EXPECT_FALSE(ToString(code).empty());
        names.insert(ToString(code));
    }
    EXPECT_EQ(names.size(), 3u);
}

// Proves: two errors with the same code and message are equal.
TEST(ErrorTest, SameCodeAndMessageAreEqual)
{
    const Error a{ErrorCode::JobThrewException, "boom"};
    const Error b{ErrorCode::JobThrewException, "boom"};
    EXPECT_EQ(a, b);
}

// Proves: a different code, or a different message, makes errors unequal.
TEST(ErrorTest, DifferentCodeOrMessageAreNotEqual)
{
    const Error base{ErrorCode::JobThrewException, "boom"};
    EXPECT_NE(base, (Error{ErrorCode::JobThrewUnknown, "boom"}));
    EXPECT_NE(base, (Error{ErrorCode::JobThrewException, "bang"}));
}