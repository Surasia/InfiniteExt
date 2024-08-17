#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <array>
#include <ctime>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>


class Logger
{
public:
    /* Operators */
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    /* Public Variables */
    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        CRITICAL,
        _ERROR
    };
    /* Public Functions */
    static Logger &GetInstance(bool useFile = false);
    /* Public Templates */
    template <typename... Args>
    void Log(Level logLevel, const std::string &formatString, Args &&...args)
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::string timestamp = GetTimestamp();
        std::string formattedMessage = std::vformat(formatString, std::make_format_args(args...));
        std::string logEntry = std::format("[{}] [{}] {}\n", timestamp, LevelToString(logLevel), formattedMessage);

        if (useFile && logFile.is_open())
        {
            logFile << logEntry;
        }
        else
        {
            std::cout << logEntry;
        }
    };

private:
    /* Operators */
    explicit Logger(bool useFile);
    ~Logger();
    /* Private Functions */
    static std::string LevelToString(Level logLevel);
    static std::string GetTimestamp();
    void OpenLogFile();
    /* Private Variables */
    bool useFile = false;
    std::ofstream logFile;
    static std::mutex mtx;
};

#endif
