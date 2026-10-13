#include <gtest/gtest.h>

#include <array>
#include <set>
#include <string_view>
#include <utility>

#include <taskscheduler/JobStateRules.h>

using namespace taskscheduler;

namespace
{
    constexpr std::array<JobState, 4> kAllStates = {
        JobState::Pending, JobState::Running, JobState::Succeeded, JobState::Failed};

    // The specification: these three moves are the only legal ones.
    const std::set<std::pair<JobState, JobState>> kValidMoves = {
        {JobState::Pending, JobState::Running},
        {JobState::Running, JobState::Succeeded},
        {JobState::Running, JobState::Failed}};
}

// Proves: the three legal moves are accepted.
TEST(JobStateTest, ValidTransitionsAreAccepted)
{
    EXPECT_TRUE(IsValidTransition(JobState::Pending, JobState::Running));
    EXPECT_TRUE(IsValidTransition(JobState::Running, JobState::Succeeded));
    EXPECT_TRUE(IsValidTransition(JobState::Running, JobState::Failed));
}

// Proves: every one of the 16 pairs is judged correctly, so the other 13 are rejected.
TEST(JobStateTest, EveryOtherPairIsRejected)
{
    for (JobState from : kAllStates)
    {
        for (JobState to : kAllStates)
        {
            const bool expected = kValidMoves.count({from, to}) > 0;
            EXPECT_EQ(IsValidTransition(from, to), expected)
                << "from " << ToString(from) << " to " << ToString(to);
        }
    }
}

// Proves: only Succeeded and Failed count as finished.
TEST(JobStateTest, TerminalStates)
{
    EXPECT_TRUE(IsTerminal(JobState::Succeeded));
    EXPECT_TRUE(IsTerminal(JobState::Failed));
    EXPECT_FALSE(IsTerminal(JobState::Pending));
    EXPECT_FALSE(IsTerminal(JobState::Running));
}

// Proves: "terminal" and "no move out" always agree, so the two functions can't drift apart.
TEST(JobStateTest, TerminalMeansNoWayOut)
{
    for (JobState state : kAllStates)
    {
        bool hasWayOut = false;
        for (JobState to : kAllStates)
        {
            if (IsValidTransition(state, to)) { hasWayOut = true; }
        }
        EXPECT_EQ(IsTerminal(state), !hasWayOut) << ToString(state);
    }
}

// Proves: each state has the expected printable name.
TEST(JobStateTest, ToStringGivesExpectedNames)
{
    EXPECT_EQ(ToString(JobState::Pending), "Pending");
    EXPECT_EQ(ToString(JobState::Running), "Running");
    EXPECT_EQ(ToString(JobState::Succeeded), "Succeeded");
    EXPECT_EQ(ToString(JobState::Failed), "Failed");
}

// Proves: names are non-empty and no two states share a name.
TEST(JobStateTest, ToStringNamesAreDistinct)
{
    std::set<std::string_view> names;
    for (JobState state : kAllStates)
    {
        EXPECT_FALSE(ToString(state).empty());
        names.insert(ToString(state));
    }
    EXPECT_EQ(names.size(), 4u);
}