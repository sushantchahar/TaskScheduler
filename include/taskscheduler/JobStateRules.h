#ifndef TASKSCHEDULER_JOBSTATERULES_H
#define TASKSCHEDULER_JOBSTATERULES_H
#include <string_view>
#include <taskscheduler/JobState.h>

namespace taskscheduler
{
    [[nodiscard]] bool IsValidTransition(JobState From, JobState To);
    [[nodiscard]] bool IsTerminal(JobState state);
    [[nodiscard]] std::string_view ToString(JobState state);
}


#endif //TASKSCHEDULER_JOBSTATERULES_H
