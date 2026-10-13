#include <cassert>
#include <taskscheduler/Job.h>
#include <taskscheduler/JobStateRules.h>
using namespace std;

taskscheduler::Job::Job(taskscheduler::JobId id, int priority, taskscheduler::Callable callable) :
_Id(id),
_Priority(priority),
_Callable(move(callable)),
_State(JobState::Pending)
{
    assert(static_cast<bool>(_Callable));
}

taskscheduler::JobId taskscheduler::Job::Id() const
{
    return _Id;
}

int taskscheduler::Job::Priority() const
{
    return _Priority;
}

JobState taskscheduler::Job::State() const
{
    return _State;
}

bool taskscheduler::Job::TransitionTo(JobState state)
{
    if (!taskscheduler::IsValidTransition(_State, state))
    {
        return false;
    }

    _State = state;
    return true;
}

void taskscheduler::Job::Invoke()
{
    assert(_State == JobState::Running);
    _Callable();
}
