#ifndef TASKSCHEDULER_ERRORFUNCTIONS_H
#define TASKSCHEDULER_ERRORFUNCTIONS_H
#include <string_view>
#include <taskscheduler/ErrorCode.h>

namespace taskscheduler
{
    std::string_view ToString(ErrorCode code);
}

#endif //TASKSCHEDULER_ERRORFUNCTIONS_H
