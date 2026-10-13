#ifndef TASKSCHEDULER_JOBID_H
#define TASKSCHEDULER_JOBID_H
#include <cstdint>
#include <compare>
#include <functional>
using namespace std;

namespace taskscheduler
{
    struct JobId
    {
    public:
        uint64_t value = 0; // default 0 means no job
        constexpr JobId() = default;
        constexpr explicit JobId(uint64_t value) : value(value) {}
        constexpr static JobId Invalid() {return JobId{};}
        constexpr bool IsValid() const {return value != 0;}
        friend constexpr auto operator<=>(const JobId&, const JobId&) = default;
    };
}

namespace std
{
    template <>
    struct hash<taskscheduler::JobId>
    {
        std::size_t operator()(const taskscheduler::JobId& id) const noexcept
        {
            return hash<uint64_t>{}(id.value);
        }
    };
}

#endif //TASKSCHEDULER_JOBID_H
