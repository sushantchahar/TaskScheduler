#ifndef TASKSCHEDULER_JOB_H
#define TASKSCHEDULER_JOB_H
#include <taskscheduler/JobState.h>
#include <taskscheduler/JobId.h>
#include <functional>
namespace taskscheduler
{
    using Callable = std::function<void()>;
    class Job
    {
    private:
        taskscheduler::JobId _Id;
        int _Priority;
        taskscheduler::Callable _Callable;
        JobState _State;

    public:
        Job(const Job&) = delete;
        Job(Job&&) noexcept = default;
        Job& operator=(const Job&) = delete;
        Job& operator=(Job&&) noexcept = default;

        // Custom constructor to build a Job object
        Job(taskscheduler::JobId id, int priority, taskscheduler::Callable callable);

        taskscheduler::JobId Id() const;
        int Priority() const;
        JobState State() const;
        [[nodiscard]] bool TransitionTo(JobState state);
        void Invoke();
    };
}


#endif //TASKSCHEDULER_JOB_H
