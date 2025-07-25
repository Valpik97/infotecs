
#include "logger/LoggerFile.h"
#include "logger/ILogger.h"

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <mutex>
#include <filesystem>

namespace logger {

// Convert log level enum to string
const char* logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Info:    return "INFO";
        default:                return "UNKNOWN";
    }
}

// Constructor: open log file and write BOM if needed
LoggerFile::LoggerFile(const std::string &filename, LogLevel level, bool emitBOM)
    : m_filename(filename), m_logLevel(level), m_emitBOM(emitBOM) {

    bool isEmpty = !std::filesystem::exists(filename) || 
                   std::filesystem::file_size(filename) == 0;

    m_file.open(filename, std::ios::app | std::ios::binary);

    if (!m_file.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }

    // Write BOM if file is empty
    if (isEmpty && m_emitBOM) {
        const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        m_file.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    }
}

LoggerFile::~LoggerFile() {
    m_file.close();
}

// Log a message if level is sufficient
void LoggerFile::log(const std::string &message, LogLevel level) {
    if (level > m_logLevel) return;

    std::lock_guard<std::mutex> lock(m_mutex);
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    m_file << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] "
           << "[" << logLevelToString(level) << "] "
           << message << std::endl;
    m_file.flush();
}

// Change log level
void LoggerFile::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_logLevel = level;
}

// Get current time as string
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

