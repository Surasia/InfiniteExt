#include "Logger.hpp"

std::mutex Logger::mtx;

Logger& Logger::GetInstance(bool useFile) 
{
	static Logger instance(useFile);
	return instance;
}

Logger::Logger(bool useFile) : useFile(useFile) 
{
	if (useFile) {
		OpenLogFile();
	}
}

Logger::~Logger() 
{
	if (logFile.is_open()) {
		logFile.close();
	}
}

std::string Logger::LevelToString(Level logLevel) 
{
	switch (logLevel) {
	case DEBUG: return "DEBUG";
	case INFO: return "INFO";
	case WARNING: return "WARNING";
	case CRITICAL: return "CRITICAL";
	case _ERROR: return "ERROR";
	default: return "UNKNOWN";
	}
}

std::string Logger::GetTimestamp() 
{
	time_t now = time(0);
	struct tm timeinfo;
	char buffer[20];
	localtime_s(&timeinfo, &now);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
	return std::string(buffer);
}

void Logger::OpenLogFile() 
{
	std::string filename = "./InfExt.log";
	logFile.open(filename, std::ios::app);
	if (!logFile.is_open()) {
		useFile = false;
	}
}
