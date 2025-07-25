#include "logger/LoggerFile.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace logger;

void test_log_levels() {
    const char* filename = "test_log.txt";
    std::remove(filename);
    LoggerFile logger(filename, LogLevel::Warning, false);

    logger.log("This is info", LogLevel::Info);      // Should not log
    logger.log("This is warning", LogLevel::Warning); // Should log
    logger.log("This is error", LogLevel::Error);     // Should log

    std::ifstream file(filename);
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        ++count;
        if (line.find("INFO") != std::string::npos) assert(false && "Info should not be logged");
    }
    assert(count == 2 && "Should log only warning and error");
    file.close();
    std::remove(filename);
}

void test_change_log_level() {
    const char* filename = "test_log2.txt";
    std::remove(filename);
    LoggerFile logger(filename, LogLevel::Error, false);
    logger.log("Should log error", LogLevel::Error); // Should log
    logger.log("Should not log warning", LogLevel::Warning); // Should not log
    logger.setLogLevel(LogLevel::Info);
    logger.log("Should log info", LogLevel::Info); // Should log

    std::ifstream file(filename);
    std::string line;
    int count = 0;
    bool found_info = false, found_error = false;
    while (std::getline(file, line)) {
        ++count;
        if (line.find("INFO") != std::string::npos) found_info = true;
        if (line.find("ERROR") != std::string::npos) found_error = true;
    }
    assert(count == 2 && found_info && found_error && "Should log error and info only");
    file.close();
    std::remove(filename);
}

int main() {
    test_log_levels();
    test_change_log_level();
    std::cout << "All logger tests passed!\n";
    return 0;
} 