#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include <unordered_set>
#include <taskscheduler/JobId.h>

using taskscheduler::JobId;
/*
TEST(JobIdTest, InvalidIdHasValueZeroAndIsNotValid)
{
    EXPECT_EQ(JobId::Invalid().value, 0u);
    EXPECT_FALSE(JobId::Invalid().IsValid());
}

TEST(JobIdTest, DefaultConstructedIdIsInvalid)
{
    EXPECT_FALSE(JobId{}.IsValid());
    EXPECT_EQ(JobId{}, JobId::Invalid());
}

TEST(JobIdTest, AssignedIdIsValid)
{
    EXPECT_TRUE(JobId{1}.IsValid());
}

TEST(JobIdTest, EqualValuesCompareEqual)
{
    EXPECT_EQ(JobId{5}, JobId{5});
    EXPECT_NE(JobId{5}, JobId{6});
}

TEST(JobIdTest, OrderingFollowsValue)
{
    EXPECT_LT(JobId{3}, JobId{4});
    EXPECT_GT(JobId{4}, JobId{3});
    EXPECT_LE(JobId{4}, JobId{4});
    EXPECT_GE(JobId{4}, JobId{4});
}

TEST(JobIdTest, CanBeUsedInUnorderedSet)
{
    std::unordered_set<JobId> ids;
    ids.insert(JobId{7});
    EXPECT_EQ(ids.count(JobId{7}), 1u);
    EXPECT_EQ(ids.count(JobId{8}), 0u);
}

TEST(JobIdTest, CannotBeCreatedImplicitlyFromANumber)
{
    // static_assert(!std::is_convertible_v<std::uint64_t, JobId>);
}
*/