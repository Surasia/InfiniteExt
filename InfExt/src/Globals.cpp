#include "Globals.hpp"
#include "Logger/Logger.hpp"

uintptr_t ModuleBase = 0;

uintptr_t GetModuleBase()
{
	Logger& logger = Logger::GetInstance(false);
	if (ModuleBase != 0) {
		return ModuleBase;
	}
	else {
		logger.Log(Logger::WARNING, "ModuleBase is not set!");
		return 0;
	}
}
