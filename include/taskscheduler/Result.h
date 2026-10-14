#ifndef TASKSCHEDULER_RESULT_H
#define TASKSCHEDULER_RESULT_H
#include <optional>
#include <taskscheduler/Error.h>

namespace taskscheduler
{
    template <typename T>
    class Result;

    template <>
    class [[nodiscard]] Result<void>
    {
    public:
        static Result Ok();
        static Result Fail(Error error);
        bool IsOk() const;
        const Error& GetError() const;

    private:
        Result() = default;
        std::optional<Error> _Error;
    };
}


#endif //TASKSCHEDULER_RESULT_H
