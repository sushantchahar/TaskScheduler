#include <taskscheduler/Result.h>
#include <utility>
using namespace taskscheduler;

Result<void> Result<void>::Ok()
{
    return Result{};
}

Result<void> Result<void>::Fail(Error error)
{
    Result result;
    result._Error = std::move(error);
    return result;
}

bool Result<void>::IsOk() const
{
    return !_Error.has_value();
}

const Error& Result<void>::GetError() const
{
    return _Error.value();
}
