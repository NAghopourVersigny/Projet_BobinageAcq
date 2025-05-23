#include "../include/Logger.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std; // ajoute ce using une fois en haut

Logger::Logger(const string& filename, bool logToConsole)
    : start(chrono::steady_clock::now()), consoleOutput(logToConsole)
{
    logFile.open(filename, ios::app);
    if (!logFile) {
        cerr << "Erreur : impossible d'ouvrir le fichier de log.\n";
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(Level level, const string& message) {

    ostringstream fullMessage;
    fullMessage << "[" << currentTimestamp() << "] "
                << "[" << elapsedTime() << "] "
                << "[" << levelToString(level) << "] "
                << message;

    if (logFile.is_open())
        logFile << fullMessage.str() << endl;

   /* if (consoleOutput)
        cout << fullMessage.str() << endl;*/
}

void Logger::info(const string& msg)    { log(INFO, msg); }
void Logger::warning(const string& msg) { log(WARNING, msg); }
void Logger::error(const string& msg)   { log(ERROR, msg); }

string Logger::currentTimestamp() {
    using namespace chrono;
    auto now = system_clock::now();
    auto now_time_t = system_clock::to_time_t(now);
    auto now_ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    tm tm_info;
#ifdef _WIN32
    localtime_s(&tm_info, &now_time_t);
#else
    localtime_r(&now_time_t, &tm_info);
#endif

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_info);

    ostringstream oss;
    oss << buffer << "." << setfill('0') << setw(3) << now_ms.count();
    return oss.str();
}

string Logger::elapsedTime() {
    using namespace chrono;
    auto now = steady_clock::now();
    auto elapsed = duration_cast<milliseconds>(now - start).count();
    ostringstream oss;
    oss << elapsed << "ms";
    return oss.str();
}

string Logger::levelToString(Level level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}