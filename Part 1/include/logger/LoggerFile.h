#pragma once
#include "ILogger.h"
#include <fstream>
#include <mutex>

namespace logger {

class LoggerFile : public ILogger {
public:
    LoggerFile(const std::string& filename, LogLevel level);
    ~LoggerFile();

    void log(const std::string& message, LogLevel level) override;
    void setLogLevel(LogLevel level) override;

private:
    std::ofstream logFile_;
    LogLevel currentLevel_;
    std::mutex logMutex_;

    std::string getTimestamp() const;
    std::string logLevelToString(LogLevel level) const;
};

}
