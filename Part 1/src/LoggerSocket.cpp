#include "logger/LoggerSocket.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <ctime>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace logger {

LoggerSocket::LoggerSocket(const std::string& host, int port, LogLevel level)
    : currentLevel_(level) {
    sock_ = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
    connect(sock_, (struct sockaddr*)&addr, sizeof(addr));
}

LoggerSocket::~LoggerSocket() {
    close(sock_);
}

void LoggerSocket::log(const std::string& message, LogLevel level) {
    if (level < currentLevel_) return;

    std::string fullMessage = "[" + getTimestamp() + "] [" + logLevelToString(level) + "] " + message;
    std::lock_guard<std::mutex> lock(socketMutex_);
    send(sock_, fullMessage.c_str(), fullMessage.size(), 0);
}

void LoggerSocket::setLogLevel(LogLevel level) {
    currentLevel_ = level;
}

std::string LoggerSocket::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&time, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string LoggerSocket::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

}
