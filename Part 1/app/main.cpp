#include "logger/LoggerFile.h"
#include "logger/LoggerSocket.h"
#include <memory>

int main() {
    std::unique_ptr<logger::ILogger> logFile = std::make_unique<logger::LoggerFile>("logs/app.log", logger::LogLevel::INFO);
    logFile->log("File logger: Info", logger::LogLevel::INFO);
    logFile->log("File logger: Debug", logger::LogLevel::DEBUG);

    logFile->setLogLevel(logger::LogLevel::DEBUG);
    logFile->log("File logger: Now accepts debug", logger::LogLevel::DEBUG);

    std::unique_ptr<logger::ILogger> logSocket = std::make_unique<logger::LoggerSocket>("127.0.0.1", 9000, logger::LogLevel::INFO);
    logSocket->log("Socket logger: Error test", logger::LogLevel::ERROR);

    return 0;
}
