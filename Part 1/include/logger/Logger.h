#pragma once

#include <string>
#include <fstream>
#include <mutex>

namespace logger {

enum class LogLevel {
    DEBUG = 0,
    INFO,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename, LogLevel level);
    ~Logger();

    void log(const std::string& message, LogLevel level);
    void setLogLevel(LogLevel level);

private:
    std::ofstream logFile_;
    LogLevel currentLevel_;
    std::mutex logMutex_;

    std::string getTimestamp() const;
    std::string logLevelToString(LogLevel level) const;
};

} // namespace logger
