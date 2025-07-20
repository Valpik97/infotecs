#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "logger/LoggerFile.h"

using namespace logger;

std::queue<std::pair<std::string, LogLevel>> msgQueue;
std::mutex queueMutex;
std::condition_variable cv;
bool done = false;

void loggerThreadFunc(LoggerFile& logger) {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, []{ return !msgQueue.empty() || done; });

        while (!msgQueue.empty()) {
            auto [msg, level] = msgQueue.front();
            msgQueue.pop();
            lock.unlock();

            logger.log(msg, level);

            lock.lock();
        }

        if (done && msgQueue.empty()) break;
    }
}

LogLevel parseLevel(const std::string& levelStr) {
    if (levelStr == "error") return LogLevel::Error;
    if (levelStr == "warning") return LogLevel::Warning;
    return LogLevel::Info;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <logfile> [default_level]\n";
        return 1;
    }

    std::string logfile = argv[1];
    LogLevel defaultLevel = LogLevel::Info;
    if (argc >= 3) {
        defaultLevel = parseLevel(argv[2]);
    }

    LoggerFile logger(logfile, defaultLevel);

    std::thread loggerThread(loggerThreadFunc, std::ref(logger));

    while (true) {
        std::cout << "Enter message (or 'exit' to quit): ";
        std::string msg;
        std::getline(std::cin, msg);

        if (msg == "exit") break;

        std::cout << "Enter level (error, warning, info) or empty for default: ";
        std::string levelStr;
        std::getline(std::cin, levelStr);

        LogLevel lvl = levelStr.empty() ? defaultLevel : parseLevel(levelStr);

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            msgQueue.emplace(msg, lvl);
        }
        cv.notify_one();
    }

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        done = true;
    }
    cv.notify_one();
    loggerThread.join();

    return 0;
}
