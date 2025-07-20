
#include "logger/LoggerFile.h"
#include "logger/ILogger.h"

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>




namespace logger {

const char* logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Info:    return "INFO";
        default:                return "UNKNOWN";
    }
}

LoggerFile::LoggerFile(const std::string& filename, LogLevel defaultLevel)
    : logFileName_(filename), currentLevel_(defaultLevel) {}

LoggerFile::~LoggerFile() {}

void LoggerFile::log(const std::string& message, LogLevel level) {
    if (level > currentLevel_)
        return;

    std::lock_guard<std::mutex> lock(mtx_);

    std::ofstream file(logFileName_, std::ios::app | std::ios::binary); // binary — гарантирует запись байтов
    if (!file.is_open()) return;

    // Получить текущее время
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &now_time);
#else
    localtime_r(&now_time, &tm);
#endif

    std::ostringstream oss;
    oss << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
    oss << "[" << logLevelToString(level) << "] ";
    oss << message << "\n";

    file << oss.str();
}

void LoggerFile::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mtx_);
    currentLevel_ = level;
}

std::string LoggerFile::getCurrentTimeString() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} // namespace logger
