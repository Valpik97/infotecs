// LoggerFile.h
#pragma once

#include "ILogger.h"
#include <fstream>
#include <mutex>
#include <string>

namespace logger {

// File logger implementation
class LoggerFile : public ILogger {
public:
    // Initialize logger with file name and log level
    LoggerFile(const std::string& filename, LogLevel level, bool emitBOM = true);
    ~LoggerFile();

    void log(const std::string& message, LogLevel level) override;
    void setLogLevel(LogLevel level) override;

private:
    std::ofstream m_file;      // Log file stream
    std::string m_filename;    // Log file name
    LogLevel m_logLevel;       // Current log level
    std::mutex m_mutex;        // Mutex for thread safety
    bool m_emitBOM;            // Write BOM at file start

    std::string getCurrentTimeString() const; // Get current time as string
};

// Convert log level to string
const char* logLevelToString(LogLevel level);

} // namespace logger
