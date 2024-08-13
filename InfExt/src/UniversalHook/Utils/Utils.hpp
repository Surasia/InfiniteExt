#ifndef UTILS_CPP
#define UTILS_CPP

#include <Windows.h>
#include <thread>
#include <dxgi.h>

namespace Utils {
	HWND GetProcessWindow();
	void UnloadDLL();

	HMODULE GetCurrentImageBase();

	int GetCorrectDXGIFormat(int eCurrentFormat);
}

#endif