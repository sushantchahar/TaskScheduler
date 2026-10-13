#include "taskscheduler/JobStateRules.h"

bool taskscheduler::IsValidTransition(JobState From, JobState To)
{
    return (From == JobState::Pending && To == JobState::Running)
    ||
    (From == JobState::Running && To == JobState::Failed)
    ||
    (From == JobState::Running && To == JobState::Succeeded);
}

bool taskscheduler::IsTerminal(JobState state)
{
    if (state == JobState::Failed || state == JobState::Succeeded) {return true;}
    else {return false;}
}

std::string_view taskscheduler::ToString(JobState state)
{
    switch (state)
    {
        case JobState::Running:
            return "Running";
            break;
        case JobState::Failed:
            return "Failed";
            break;
        case JobState::Succeeded:
            return "Succeeded";
            break;
        case JobState::Pending:
            return "Pending";
            break;
    }

    return "Unknown";
}