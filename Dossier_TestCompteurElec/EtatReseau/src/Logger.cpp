#include "../include/Logger.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

Logger::Logger(const std::string& filename, bool logToConsole)
    : start(std::chrono::steady_clock::now()), consoleOutput(logToConsole)
{
    logFile.open(filename, std::ios::app);
    if (!logFile) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier de log.\n";
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(Level level, const std::string& message) {
    std::ostringstream fullMessage;
    fullMessage << "[" << currentTimestamp() << "] "
                << "[" << elapsedTime() << "] "
                << "[" << levelToString(level) << "] "
                << message;

    if (logFile.is_open())
        logFile << fullMessage.str() << std::endl;

    /* if (consoleOutput)
        std::cout << fullMessage.str() << std::endl */
}

void Logger::info(const std::string& msg)    { log(INFO, msg); }
void Logger::warning(const std::string& msg) { log(WARNING, msg); }
void Logger::error(const std::string& msg)   { log(ERROR, msg); }

std::string Logger::currentTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto now_time_t = system_clock::to_time_t(now);
    auto now_ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &now_time_t);
#else
    localtime_r(&now_time_t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << now_ms.count();
    return oss.str();
}

std::string Logger::elapsedTime() {
    using namespace std::chrono;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    std::ostringstream oss;
    oss << elapsed << "ms";
    return oss.str();
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}