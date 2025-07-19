#include "logger/Logger.h"
#include <iostream>

int main() {
    logger::Logger log("logs/app.log", logger::LogLevel::INFO);

    log.log("This is a DEBUG message", logger::LogLevel::DEBUG);
    log.log("This is an INFO message", logger::LogLevel::INFO);
    log.log("This is an ERROR message", logger::LogLevel::ERROR);

    std::cout << "Changing log level to DEBUG..." << std::endl;
    log.setLogLevel(logger::LogLevel::DEBUG);
    log.log("Another DEBUG message", logger::LogLevel::DEBUG);

    return 0;
}
