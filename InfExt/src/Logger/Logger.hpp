#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>  
#include <mutex>
#include <format>


class Logger {
public:
	/* Public Variables */
	enum Level { DEBUG, INFO, WARNING, CRITICAL, _ERROR };
	/* Public Functions */
	static Logger& GetInstance(bool useFile = false);
	/* Public Templates */
	template<typename... Args>
	void Log(Level logLevel, const std::string& formatString, Args&&... args) {
		std::lock_guard<std::mutex> lock(mtx);
		std::string timestamp = GetTimestamp();
		std::string formattedMessage = std::vformat(formatString, std::make_format_args(args...));
		std::string logEntry = std::format("[{}] [{}] {}\n", timestamp, LevelToString(logLevel), formattedMessage);

		if (useFile && logFile.is_open()) {
			logFile << logEntry;
		}
		else {
			std::cout << logEntry;
		}
	};

private:
	/* Operators */
	Logger(bool useFile);
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	~Logger();
	/* Private Functions */
	std::string LevelToString(Level logLevel);
	std::string GetTimestamp();
	void OpenLogFile();
	/* Private Variables */
	bool useFile;
	std::ofstream logFile;
	static std::mutex mtx;
};

#endif
