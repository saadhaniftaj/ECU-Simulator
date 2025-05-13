#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <QString>

class Logger {
public:
    Logger() = default;
    
    void log(const std::string& message) {
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        timestamp.pop_back();  // Remove newline
        logs.push_back(timestamp + " - " + message);
    }
    
    void showLastLog() const {
        if (!logs.empty()) {
            std::cout << logs.back() << std::endl;
        }
    }
    
    void showAllLogs() const {
        for (const auto& log : logs) {
            std::cout << log << std::endl;
        }
    }

    QString getAllLogsQString() const {
        QString all;
        for (const auto& log : logs) {
            all += QString::fromStdString(log) + "\n";
        }
        return all;
    }

private:
    std::vector<std::string> logs;
};

#endif // LOGGER_H 