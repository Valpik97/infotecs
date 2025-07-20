#pragma once
#include <string>

namespace logger {

enum class LogLevel {
    Error = 0,
    Warning = 1,
    Info = 2
};

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(const std::string& message, LogLevel level) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
};

} // namespace logger
