#pragma once
#include "ILogger.h"
#include <mutex>
#include <string>

namespace logger {

class LoggerSocket : public ILogger {
public:
    LoggerSocket(const std::string& host, int port, LogLevel level);
    ~LoggerSocket();

    void log(const std::string& message, LogLevel level) override;
    void setLogLevel(LogLevel level) override;

private:
    int sock_;
    LogLevel currentLevel_;
    std::mutex socketMutex_;

    std::string getTimestamp() const;
    std::string logLevelToString(LogLevel level) const;
};

}
