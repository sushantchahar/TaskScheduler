#ifndef TASKSCHEDULER_ERRORCODE_H
#define TASKSCHEDULER_ERRORCODE_H

namespace taskscheduler
{
    enum class ErrorCode
    {
        EmptyCallable,
        JobThrewException,
        JobThrewUnknown
    };
}

#endif //TASKSCHEDULER_ERRORCODE_H
