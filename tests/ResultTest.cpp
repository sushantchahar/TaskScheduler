#include <gtest/gtest.h>
#include <optional>
#include <taskscheduler/Result.h>

using namespace taskscheduler;

// Proves: Ok reports success.
TEST(ResultVoidTest, OkIsOk)
{
    auto result = Result<void>::Ok();
    EXPECT_TRUE(result.IsOk());
}

// Proves: Fail reports failure and keeps the exact error it was given.
TEST(ResultVoidTest, FailIsNotOkAndKeepsError)
{
    const Error error{ErrorCode::EmptyCallable, "job has no work"};
    auto result = Result<void>::Fail(error);

    EXPECT_FALSE(result.IsOk());
    EXPECT_EQ(result.GetError(), error);
}

// Proves: asking an Ok result for its error is a caught misuse, not undefined behavior.
TEST(ResultVoidTest, GetErrorOnOkThrows)
{
    auto result = Result<void>::Ok();
    EXPECT_THROW(result.GetError(), std::bad_optional_access);
}

// Proves: copying a failed result keeps its error.
TEST(ResultVoidTest, CopyKeepsTheError)
{
    auto original = Result<void>::Fail(Error{ErrorCode::JobThrewUnknown, "x"});
    auto copy = original;

    EXPECT_FALSE(copy.IsOk());
    EXPECT_EQ(copy.GetError(), original.GetError());
}