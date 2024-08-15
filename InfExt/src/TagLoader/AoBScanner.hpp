#ifndef AOBSCANNER_HPP
#define AOBSCANNER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

class Aob {
public:
	/* Public Functions */
	static uintptr_t AOBScan(uintptr_t startAddress, const char* pattern);
private:
	/* Private Functions */
	static bool compare(const BYTE* pData, const std::vector<int>& pattern);
	static uintptr_t findPattern(uintptr_t baseAddress, size_t size, const std::vector<int>& pattern);
};

#endif
