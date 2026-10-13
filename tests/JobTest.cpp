#include <gtest/gtest.h>

#include <stdexcept>
#include <type_traits>
#include <utility>

#include <taskscheduler/Job.h>

using namespace taskscheduler;

// Proves: a new job starts Pending and remembers what it was given.
TEST(JobTest, NewJobIsPendingAndKeepsIdAndPriority)
{
    Job job{JobId{42}, 7, [] {}};

    EXPECT_EQ(job.State(), JobState::Pending);
    EXPECT_EQ(job.Id(), JobId{42});
    EXPECT_EQ(job.Priority(), 7);
}

// Proves: the success path works end to end.
TEST(JobTest, FullPathToSucceeded)
{
    Job job{JobId{1}, 0, [] {}};

    EXPECT_TRUE(job.TransitionTo(JobState::Running));
    EXPECT_EQ(job.State(), JobState::Running);
    EXPECT_TRUE(job.TransitionTo(JobState::Succeeded));
    EXPECT_EQ(job.State(), JobState::Succeeded);
}

// Proves: the failure path works end to end.
TEST(JobTest, FullPathToFailed)
{
    Job job{JobId{1}, 0, [] {}};

    EXPECT_TRUE(job.TransitionTo(JobState::Running));
    EXPECT_TRUE(job.TransitionTo(JobState::Failed));
    EXPECT_EQ(job.State(), JobState::Failed);
}

// Proves: an illegal move is refused AND leaves the state untouched.
TEST(JobTest, InvalidTransitionIsRejectedAndStateUnchanged)
{
    Job job{JobId{1}, 0, [] {}};

    EXPECT_FALSE(job.TransitionTo(JobState::Succeeded));  // skipping Running
    EXPECT_EQ(job.State(), JobState::Pending);
    EXPECT_FALSE(job.TransitionTo(JobState::Pending));    // same state
    EXPECT_EQ(job.State(), JobState::Pending);
}

// Proves: a finished job can never move again.
TEST(JobTest, FinishedJobRejectsEveryTransition)
{
    Job job{JobId{1}, 0, [] {}};
    ASSERT_TRUE(job.TransitionTo(JobState::Running));
    ASSERT_TRUE(job.TransitionTo(JobState::Succeeded));

    EXPECT_FALSE(job.TransitionTo(JobState::Pending));
    EXPECT_FALSE(job.TransitionTo(JobState::Running));
    EXPECT_FALSE(job.TransitionTo(JobState::Succeeded));
    EXPECT_FALSE(job.TransitionTo(JobState::Failed));
    EXPECT_EQ(job.State(), JobState::Succeeded);
}

// Proves: Invoke runs the work exactly once.
TEST(JobTest, InvokeRunsCallableOnce)
{
    int counter = 0;
    Job job{JobId{1}, 0, [&counter] { ++counter; }};
    ASSERT_TRUE(job.TransitionTo(JobState::Running));

    job.Invoke();

    EXPECT_EQ(counter, 1);
}

// Proves: Job does not hide errors; the scheduler will catch them.
TEST(JobTest, ExceptionFromCallablePropagates)
{
    Job job{JobId{1}, 0, [] { throw std::runtime_error("boom"); }};
    ASSERT_TRUE(job.TransitionTo(JobState::Running));

    EXPECT_THROW(job.Invoke(), std::runtime_error);
}

// Proves: copying is forbidden, moving is allowed and never throws.
// static_assert is checked at compile time, so if this file compiles, these hold.
TEST(JobTest, CopyAndMoveRules)
{
    static_assert(!std::is_copy_constructible_v<Job>);
    static_assert(!std::is_copy_assignable_v<Job>);
    static_assert(std::is_nothrow_move_constructible_v<Job>);
    static_assert(std::is_nothrow_move_assignable_v<Job>);
    SUCCEED();
}

// Proves: move construction carries everything over.
TEST(JobTest, MoveConstructedJobKeepsEverything)
{
    int counter = 0;
    Job source{JobId{3}, 9, [&counter] { ++counter; }};
    ASSERT_TRUE(source.TransitionTo(JobState::Running));

    Job moved{std::move(source)};  // do not touch `source` after this line

    EXPECT_EQ(moved.Id(), JobId{3});
    EXPECT_EQ(moved.Priority(), 9);
    EXPECT_EQ(moved.State(), JobState::Running);
    moved.Invoke();
    EXPECT_EQ(counter, 1);
}

// Proves: move assignment replaces the target with the source's data.
TEST(JobTest, MoveAssignedJobTakesSourceData)
{
    Job source{JobId{3}, 9, [] {}};
    ASSERT_TRUE(source.TransitionTo(JobState::Running));
    Job target{JobId{1}, 1, [] {}};

    target = std::move(source);  // do not touch `source` after this line

    EXPECT_EQ(target.Id(), JobId{3});
    EXPECT_EQ(target.Priority(), 9);
    EXPECT_EQ(target.State(), JobState::Running);
}

// Proves: running a job that is not Running is caught (Debug builds only).
#ifndef NDEBUG
TEST(JobDeathTest, InvokeOnPendingJobAborts)
{
    Job job{JobId{1}, 0, [] {}};

    EXPECT_DEATH(job.Invoke(), "");
}
#endif