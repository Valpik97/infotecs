#pragma once

#include "ILogger.h"
#include <string>
#include <mutex>

namespace logger {

class LoggerFile : public ILogger {
public:
    LoggerFile(const std::string& filename, LogLevel defaultLevel);
    ~LoggerFile();

    void log(const std::string& message, LogLevel level) override;
    void setLogLevel(LogLevel level) override;

private:
    std::string logFileName_;
    LogLevel currentLevel_;
    std::mutex mtx_;

    std::string getCurrentTimeString() const;
};

} // namespace logger
