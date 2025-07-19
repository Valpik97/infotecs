#pragma once
#include <string>

namespace logger {

enum class LogLevel {
    DEBUG = 0,
    INFO,
    ERROR
};

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message, LogLevel level) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
};

}
