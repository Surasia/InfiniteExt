#ifndef UTILS_CPP
#define UTILS_CPP

#include <Windows.h>
#include <dxgi.h>
#include <thread>

namespace Utils
{
HWND GetProcessWindow();
void UnloadDLL();

HMODULE GetCurrentImageBase();

int GetCorrectDXGIFormat(int eCurrentFormat);
} // namespace Utils

#endif
