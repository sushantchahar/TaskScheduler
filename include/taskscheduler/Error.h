#ifndef TASKSCHEDULER_ERROR_H
#define TASKSCHEDULER_ERROR_H
#include <string>
#include <taskscheduler/ErrorCode.h>

namespace taskscheduler
{
    struct Error
    {
        taskscheduler::ErrorCode code;
        std::string message;
        friend bool operator==(const Error&, const Error&) = default;
    };
}


#endif //TASKSCHEDULER_ERROR_H
