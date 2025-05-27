#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <chrono>

class Logger {
public:
    enum Level { INFO, WARNING, ERROR };

    Logger(const std::string& filename, bool logToConsole = false);
    ~Logger();

    void log(Level level, const std::string& message);
    void info(const std::string& msg);
    void warning(const std::string& msg);
    void error(const std::string& msg);

private:
    std::ofstream logFile;
    std::chrono::steady_clock::time_point start;
    bool consoleOutput;

    std::string currentTimestamp();
    std::string elapsedTime();
    std::string levelToString(Level level);
};

#endif // LOGGER_H