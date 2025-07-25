#pragma once
#include <string>

namespace logger {

// Log message importance levels
enum class LogLevel {
    Error = 0,
    Warning = 1,
    Info = 2
};

// Logger interface
class ILogger {
public:
    virtual ~ILogger() = default;

    // Log a message with a given level
    virtual void log(const std::string& message, LogLevel level) = 0;
    // Change the default log level
    virtual void setLogLevel(LogLevel level) = 0;
};

} // namespace logger
