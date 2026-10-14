#include <taskscheduler/ErrorFunctions.h>
using namespace taskscheduler;

std::string_view ToString(ErrorCode code)
{
    switch (code)
    {
    case ErrorCode::EmptyCallable:
        return "EmptyCallable";
    case ErrorCode::JobThrewException:
        return "JobThrewException";
    case ErrorCode::JobThrewUnknown:
        return "JobThrewUnknown";
    }

    return "Unknown";
}
