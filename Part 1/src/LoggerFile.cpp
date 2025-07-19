#include "logger/LoggerFile.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

namespace logger {

LoggerFile::LoggerFile(const std::string& filename, LogLevel level)
    : currentLevel_(level) {
    logFile_.open(filename, std::ios::app);
}

LoggerFile::~LoggerFile() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void LoggerFile::log(const std::string& message, LogLevel level) {
    if (level < currentLevel_ || !logFile_.is_open()) return;

    std::lock_guard<std::mutex> lock(logMutex_);
    logFile_ << "[" << getTimestamp() << "] "
             << "[" << logLevelToString(level) << "] "
             << message << std::endl;
}

void LoggerFile::setLogLevel(LogLevel level) {
    currentLevel_ = level;
}

std::string LoggerFile::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&time, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string LoggerFile::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

}
