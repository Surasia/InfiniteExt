#include "AoBScanner.hpp"

bool Aob::compare(const BYTE* pData, const std::vector<int>& pattern) 
{
    for (size_t i = 0; i < pattern.size(); ++i, ++pData) {
        if (pattern[i] != -1 && *pData != pattern[i]) {
            return false;
        }
    }
    return true;
}

uintptr_t Aob::findPattern(uintptr_t baseAddress, size_t size, const std::vector<int>& pattern) 
{

    for (uintptr_t i = 0; i < size; ++i) {
        if (compare(reinterpret_cast<const BYTE*>(baseAddress + i), pattern)) {
            return baseAddress + i;
        }
    }
    return 0;
}

uintptr_t Aob::AOBScan(uintptr_t startAddress, const char* pattern) 
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    uintptr_t endAddress = reinterpret_cast<uintptr_t>(sysInfo.lpMaximumApplicationAddress);
    uintptr_t currentAddress = startAddress;

    std::vector<int> patternBytes;
    std::istringstream iss(pattern);
    std::string byteStr;
    while (iss >> byteStr) {
        if (byteStr == "??") {
            patternBytes.push_back(-1);
        }
        else {
            patternBytes.push_back(static_cast<int>(strtoul(byteStr.c_str(), nullptr, 16)));
        }
    }

    while (currentAddress < endAddress) {
        MEMORY_BASIC_INFORMATION memInfo;
        if (VirtualQuery(reinterpret_cast<LPCVOID>(currentAddress), &memInfo, sizeof(memInfo)) == 0) {
            break;
        }

        if (memInfo.State == MEM_COMMIT &&
            (memInfo.Protect == PAGE_EXECUTE_READWRITE ||
                memInfo.Protect == PAGE_READWRITE ||
                memInfo.Protect == PAGE_READONLY ||
                memInfo.Protect == PAGE_EXECUTE_READ)) {
            uintptr_t foundAddress = findPattern(currentAddress, memInfo.RegionSize, patternBytes);
            if (foundAddress) {
                return foundAddress;
            }
        }
        currentAddress += memInfo.RegionSize;
    }

    return 0;
}
